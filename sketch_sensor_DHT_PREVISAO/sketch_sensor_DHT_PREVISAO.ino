// Biblioteca.
#include "DHT.h"

// Macro
#define DHTTYPE DHT22
#define DHTPIN 2

DHT dht(DHTPIN, DHTTYPE);
// Variáveis de controle de tempo.
unsigned long previousMillis = 0;
unsigned long previousPrintMillis = 0;

// Variável para intervalo de leitura de cinco milisegundos (para testar rapidamente).
const unsigned long INTERVALO_LEITURA = 50000;
const unsigned long INTERVALO_PRINT = 1000;
// Variável para testes reais, com quatro horas de duração para cada período.
// const unsigned long INTERVALO_LEITURA = 14400000;

// Estado do sistema.
// manhã=0, tarde=1, noite=2.
uint8_t periodoAtual = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {
    ;  // Aguarda a conexão da porta serial nativa.
  }
  inicializarSistema();
  Serial.println(F("Aguardando dois segundos para estabilização do sensor..."));
  delay(2000);  // Único delay aceitável, poís roda só uma vez no boot.

  Serial.println(F("----Realizando medição inicial----"));
  realizarLeitura();
  avancarPeriodo();

  previousMillis = millis();  // Reseta o cronômetro para o próximo ciclo a contar a partir de agora.
  previousPrintMillis = millis(); // Ampulheta.
  Serial.println(F("----Iniciando o cronômetro----"));
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();

  if(currentMillis - previousPrintMillis >= INTERVALO_PRINT){
    previousPrintMillis = currentMillis;
    unsigned long tempoPassado = currentMillis - previousMillis;
    unsigned long tempoFaltante = INTERVALO_PRINT - tempoPassado;
    // Imprimindo o cronômetro.
    Serial.print(F("[Cronômetro] Tempo atual: "));
    Serial.print(currentMillis);
    Serial.print(F(" Última medição: "));
    Serial.print(previousMillis);
    Serial.print(F(" Dispara em: "));
    Serial.print(tempoFaltante);
    Serial.println(F(" ms"));

  }

  if (currentMillis - previousMillis >= INTERVALO_LEITURA) {
    previousMillis = currentMillis;

    // Execução das tarefas.
    realizarLeitura();
    avancarPeriodo();
  }
}

// Funções
void inicializarSistema() {
  // Uso da macro F() economiza memória SRAM guardando o texto na memória Flash.
  Serial.println(F("== Sistema de monitoramento SmartPai Iniciado"));
  Serial.println(F("Aguardando o primeiro ciclo de leitura..."));
  dht.begin();
}

void realizarLeitura() {
  // Leitura de temperatura e umidade.
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  // Avaliar a leitura.
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println(F("ERRO: Falha na comunicação com o sensor DHT22. Verifique as conexões!"));
    return;  // Interrompe os dados falsos.
  }
  exibirDados(temperatura, umidade);
}

void exibirDados(float temp, float umi) {
  Serial.print(F("["));
  imprimirPeriodo();
  Serial.print(F("]"));

  Serial.print(F("Temperatura: "));
  Serial.print(temp);
  Serial.print(F("°C | "));

  Serial.print(F("Umidade: "));
  Serial.print(umi);
  Serial.println(F("%"));
}

void avancarPeriodo() {
  periodoAtual++;
  if (periodoAtual > 2) {
    periodoAtual = 0;  // Volta para manhã
  }
}

void imprimirPeriodo() {
  switch (periodoAtual) {
    case 0:
      Serial.print(F("Manhã"));
      break;
    case 1:
      Serial.print(F("Tarde"));
      break;
    case 2:
      Serial.print(F("Noite"));
      break;
    default:
      Serial.print(F("ERRO"));
      break;
  }
}
