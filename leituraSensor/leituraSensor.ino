#include "DHT.h"
#define DHTTYPE DHT22
#define DHTPIN 2

DHT dht(DHTPIN, DHTTYPE);
unsigned long tempoAnterior = 0;
const unsigned long INTERVALO_LEITURA = 3600000;
bool stateLed = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  dht.begin();
  Serial.println("\t\tTreinamentos Arduino");
  Serial.println(F("\t Como está a temperatura hoje?"));
}
void loop() {
  unsigned long tempoAtual = millis();
  if (tempoAtual - tempoAnterior >= INTERVALO_LEITURA) {
    tempoAnterior = tempoAtual;
    stateLed = !stateLed;
    digitalWrite(LED_BUILTIN, stateLed ? HIGH : LOW);

    // Capturando leitura quando o estado do led for alto.
    if (stateLed) {
      float temperatura = dht.readTemperature();
      float umidade = dht.readHumidity();
      if (isnan(temperatura) || isnan(umidade)) {
        Serial.println(F("\t Falha na leitura do sensor DHT!"));
      } else {
        Serial.print(F("\t Temperatura: "));
        Serial.print(temperatura);
        Serial.println(F(" °C"));
        Serial.print(F("\t Umidade: "));
        Serial.print(umidade);
        Serial.println(F(" %"));
      }
    } else {
      Serial.println(F("\t Aguardando próxima leitura..."));
    }
  }
}