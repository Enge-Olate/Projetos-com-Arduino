// Biblioteca Adafruit.
#include <Adafruit_Sensor.h>
#include "DHT.h"
// Configuração de hardware.
#define DHTPIN 2       // Pino de leitura do sensor.
#define DHTTYPE DHT22  // Definindo o modelo do sensor.

DHT dht(DHTPIN, DHTTYPE);

// Variáveis de controle de tempo.
unsigned long previousMillis = 0;

// Variável para intervalo de leitura de cinco milisegundos (para testar rapidamente).
// const unsigned long INTERVALO_LEITURA = 5000;

// Variável para testes reais, com oito horas de duração para cada período.
const unsigned long INTERVALO_LEITURA = 28800000;

// Estado do sistema.
// manhã=0, tarde=1, noite=2.
uint8_t periodoAtual = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ;  // Aguarda a conexão da porta serial nativa.
  }
  inicializarSistema();
  Serial.println(F("Aguardando dois segundos para estabilização do sensor..."));
  delay(2000); // Único delay aceitável, poís roda só uma vez no boot.

  Serial.println(F("----Realizando medição inicial----"));
  realizarLeitura();
  avancarPeriodo();

  previousMillis = millis(); // Reseta o cronômetro para o próximo ciclo a contar a partir de agora.  
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
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
  Serial.print(F(" °C | "));

  Serial.print(F("Umidade: "));
  Serial.print(umi);
  Serial.println(F(" %"));
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
