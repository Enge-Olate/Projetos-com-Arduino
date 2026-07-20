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

//=============== VARIÁVEIS =====================
float temperatura = 0;
float umidade = 0;
unsigned long tempoAnterior = 0;
int modo = 0;  // 0 = TEMPERATURA -> 1 = UMIDADE
// ================= SETUP =================
void setup() {
  Serial.begin(115200);
  Serial.println(F("\tDHT22 SENSOR"));
  dht.begin();

  for (int i = 0; i < 8; i++) {
    pinMode(segmentos[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(transistores[i], OUTPUT);
  }
}

void mostrarDigito(int pos, int numero, bool ponto) {

  // Desliga todos
  for (int i = 0; i < 4; i++) {
    digitalWrite(transistores[i], HIGH);
  }

  // Segmentos
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentos[i], numeros[numero][i]);
  }

  // Ponto decimal
  digitalWrite(segmentos[7], ponto ? HIGH : LOW);

  // Liga o dígito
  digitalWrite(transistores[pos], LOW);

  delay(3);
}

// ================= MOSTRADOR =================
void mostrarValor(float valor) {

  int v = (int)(valor * 100);  // ex: 25.3 → 253

  int t1 = (v / 1000) % 10;
  int t2 = (v / 100) % 10;
  int t3 = (v / 10) % 10;
  int t4 = v % 10;

  for (int i = 0; i < 50; i++) {
    if (!v || !A0) {
      digitalWrite(segmentos[7], HIGH);
    } else {

      mostrarDigito(0, t1, false);
      mostrarDigito(1, t2, true);  // decimal
      mostrarDigito(2, t3, false);
      mostrarDigito(3, t4, false);
    }
  }
}


// ================= LOOP =================
void loop() {

  // Alternância a cada 3 segundos
  if (millis() - tempoAnterior > 3000) {
    tempoAnterior = millis();
    modo = !modo;

    // Atualiza leitura (DHT é lento → evita ler toda hora)
    temperatura = dht.readTemperature();
    umidade = dht.readHumidity();
  }

  // Verifica erro
  if (isnan(temperatura) || isnan(umidade)) {
    return;
  }

  // Exibição
  if (modo == 0) {
    Serial.print(F("\t Temperatura: "));
    Serial.println(temperatura);
    mostrarValor(temperatura);  // Temperatura
  } else {
    mostrarValor(umidade);  // Umidade
    Serial.print(F("\t Umidade: "));
    Serial.println(umidade);
  }
}