#include <AM2302-Sensor.h>
#define sensor 8

AM2302::AM2302_Sensor am2302{2};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){;}
  pinMode(sensor, OUTPUT);
  digitalWrite(sensor, 1);
  if(am2302.begin()){
    delay(3000);
  }else {
    while (true) {
    Serial.println("Erro: sensor mal conectado");
    delay(10000);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  auto status = am2302.read();
  Serial.print("\n\n Status do sensor read(): ");
  Serial.println(status);
  Serial.println();
  Serial.print("Temperatura: ");
  Serial.println(am2302.get_Temperature());
  Serial.println();
  Serial.print("Umidade: ");
  Serial.println(am2302.get_Humidity());
  delay(20000);
}
