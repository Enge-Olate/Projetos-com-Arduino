/*
    Enge-Olate
    Data: 04/12/2022

      Algoritímo criado com a função de se evitar o efeito "Repique"(bounce) causado por acionemtos de chaves
    mecânicas ou relés.
        
*/
//======Mapeamento de periféricos==========
#define botao 10                        //Definindo o pino 10 para o botão.
#define ledRed 13                       //Definindo o pino 13 para o led.

//===========Fim==========
//=========Variáveis globais========
byte estado;                            //variável auxiliar para controle do nível do botão.     
//===========Fim===============
//=======Configuração da placa (Arduino Uno)=========
void setup() {

  pinMode(botao, INPUT_PULLUP);           //Configurando pino do botão como entrada de dados, utilizando o resistor interno do chip o deixando em nível alto.
  pinMode(ledRed, OUTPUT);                //Cconfigurando pino do led como saída de dados.
  
  Serial.begin(9600);                     //Configurando comunicação serial. 
}
//=======Fim======

//========Função para atenuar o efeito "Repique"======
byte semRepique(byte valor) {
  static byte ultimoValor = HIGH;         //variável para receber o estado do botão
  static unsigned long time = 500;        //variável para definair um tempo de 500ms
  static unsigned long ultimoAperto = 0;  //variável que recebe o instante em que o botão foi pressionado
  if (ultimoValor != valor) {             //Quando o botão for pressionado
    time = millis();                      //A vairiável time recebe a função millis()

    if ((millis() - ultimoAperto) > time) { //SE((tempo decorrido desde a inicilalização da placa - o ultimo click do botão) for maior que o tempo de 500ms).
      ultimoValor = valor;                  //pode-se dar novo click sem "Repique".
      return valor;                         //Retorna o nível do botão(alto ou baixo).      
    }
  }
  return HIGH;                              //
}
//=========Fim função============
//=======Função de execução======
void loop() {

  estado = digitalRead(botao);              //Estado recebe o que o pino leu.
  if (semRepique(estado) == LOW) {          //SE(a função for para nível baixo).
    digitalWrite(ledRed, !digitalRead(ledRed));//O led trocará de estado aos clicks do botão.
    Serial.println(digitalRead(ledRed));       //Para acompanhar os eventos.
  
  }

}
//=====Fim função============