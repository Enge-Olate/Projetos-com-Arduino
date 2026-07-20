#include "DHT.h"

//========== CONFIGURAÇÕES DO SENSOR DHT =======
#define DHTPIN A0
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
//=============== FIM ===========================

//=================== CONFIGURAÇÕES TRANSISTORES E DISPLAY ===========

int transistores[4] = { 2, 3, 4, 5 };
int segmentos[8] = { 6, 7, 8, 9, 10, 11, 12, 13 };
byte numeros[10][7] = {
  { 1, 1, 1, 1, 1, 1, 0 },  // 0
  { 0, 1, 1, 0, 0, 0, 0 },  // 1
  { 1, 1, 0, 1, 1, 0, 1 },  // 2
  { 1, 1, 1, 1, 0, 0, 1 },  // 3
  { 0, 1, 1, 0, 0, 1, 1 },  // 4
  { 1, 0, 1, 1, 0, 1, 1 },  // 5
  { 1, 0, 1, 1, 1, 1, 1 },  // 6
  { 1, 1, 1, 0, 0, 0, 0 },  // 7
  { 1, 1, 1, 1, 1, 1, 1 },  // 8
  { 1, 1, 1, 1, 0, 1, 1 }   // 9
};

//==================== FIM ==========================
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(F("\t DHT22 SENSOR"));
  dht.begin();
  for (int i = 0; i < 4; i++) {
    pinMode(transistores[i], OUTPUT);
  }
  for (int i = 0; i < 8; i++) {
    pinMode(segmentos[i], OUTPUT);
  }
}

void mostraDigito(int pos, int numero, bool ponto) {
  // DESLIGA TODOS OS TRANSISTORES.
  for (int i = 0; i < 4; i++) {
    digitalWrite(transistores[i], HIGH);
  }

  // SEGMENTOS
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentos[i], numeros[numero][i]);
  }

  // PONTO DECIMAL
  digitalWrite(segmentos[7], ponto ? HIGH : LOW);

  // LIGA TRANSISTOR
  digitalWrite(transistores[pos], LOW);

  delay(3);
}

void loop() {
  // put your main code here, to run repeatedly:
  float temperatura = dht.readTemperature();
  if (isnan(temperatura)) { return; }
  Serial.print(F("\t Temperatura: "));
  Serial.println(temperatura);
  int temp = (int)(temperatura * 100);  // EX: 25.4 -> 254.
  int t1 = (temp / 1000) % 10;
  int t2 = (temp / 100) % 10;
  int t3 = (temp / 10) % 10;
  int t4 = temp % 10;

  // AQUI ATUALIZA O DISPLAY
  for (int i = 0; i < 50; i++) {
    mostraDigito(0, t1, false);
    mostraDigito(1, t2, true);
    mostraDigito(2, t3, false);  // PONTO DECIMAL
    mostraDigito(3, t4, false);
  }
}
