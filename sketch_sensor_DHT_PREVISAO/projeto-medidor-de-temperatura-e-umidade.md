# PROJETO MEDIDOR DE TEMPERATURA E UMIDADE

## Visão Geral

Este projeto realiza leituras de temperatura e umidade utilizando um sensor *DHT22* em intervalos pré-definidos que simulam os períodos de manhã, tarde e noite.

## Hardware Necessário

- 1x Placa Arduíno;
- 1x Sensor DHT22;
- 1x Resistor de Pull-up de 10kohms;
- 1X Capacitor de 100Uf;
- Jumpers para conexão.

## Diagrama de Ligação
| Pino do DHT22 | Conexão no Arduíno |
| :------- | :------- |
| VCC(PINO 1)         | 5V         |
| DATA(PINO 2)         | Pino digital (com resistor 10kohms entre DATA E VCC)         |
| NC (PINO 3)         | Não conecta         |
| GND (PINO 4)          | GND|
| CAPACITOR| Entre VCC e gnd| 


## Arquitetura

**millis()** - Função para o sistema continuar rodando e verificando o relógio interno para cada período de oito horas (288800000ml), para realizar as medições. Com isso o Atmega328p poderá realizar outras operações.

**isnan()** - Prevenção de corrupção de dados, se o hardware falhar, o sensor retonará NaN (not a number). O código detecta essa anomalia e emite um alerta definido.

**F()** - Otimização de memória SRAM, essa função joga as strings para a memória flash garantindo que o programa nunca fique sem memória e trave.

## Fontes

[Arduino Docs]([https://](https://docs.arduino.cc/))

[Bibliotecas]([https://](https://docs.arduino.cc/libraries/))