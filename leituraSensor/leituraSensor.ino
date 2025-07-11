#include "DHT.h"
#define sensor 8
#define DHTTYPE DHT22
#define DHTPIN 2


DHT dht(DHTPIN, DHTTYPE);

int pisca_led() {
  /* O sensor será ligado quando o led acender*/
  pinMode(sensor, OUTPUT);
  digitalWrite(sensor, 0);
  delay(1000);
  digitalWrite(sensor, 1);
  delay(1000);
}

float leitura_temperatura() {
  float temperatura = dht.readTemperature();
  return temperatura;
}
float leitura_umidade() {
  float umidade = dht.readHumidity();
  return umidade;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pisca_led();
  dht.begin();
  Serial.println("\t\tTreinamentos Arduino");
  Serial.println(F("\t Como está a temperatura hoje?"));
}
void loop() {
  delay(500);
  if (isnan(leitura_temperatura())) {
    Serial.println(F("\t Sensor desligado!"));
    return;
  }
  byte on = pisca_led();
  if (on == 3) {
    Serial.print(F("\t Temperatura: "));
    Serial.println(leitura_temperatura());
  }
  Serial.println(on);
}