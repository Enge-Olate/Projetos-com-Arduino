/*
    Algoritmo para representação visual de código Morse.
      Data:14/12/22.
            @Enge-Olate.
                      Ref.:
                            30 Projetos com Arduíno 2º edição, Simon Monk.
*/
#define led A5  //Definindo da saída visual.

String codigo[] = { ".-", "-...", "-.-.", "-..", ".",                //A,B,C,D,E
                    "..-.", "--.", "....", "..", ".---",             //F,G,H,I,J
                    "-.-", ".-..", "--", ".-", "---",                //K,L,M,N,O
                    ".--.", "--.-", ".-.", "...", "-",               //P,Q,R,S,T
                    "..-", "...-", ".--", "-..-", "-.--", "--.." };  //U,V,W,X,Y,Z
char letra;                                                          //Variável para designar o array e comunicação serial.
int delayPonto = 200;                                                //Tempo do brilho para ponto.
int delayTraco = 600;                                                //Tempo do brilho para o traço.
void setup() {                                                       //Função para definir Quem faz o quê.

  pinMode(led, OUTPUT);     //Pino led como saída.
  Serial.begin(9600);       //Comunicação serial.
  Serial.println("Morse");  //Pritando no terminal a palavra Morse.
}  //Fim função.

void brilhoCodigo(String sequencia) {  //Função para percorrer o array de String.

  int i = 0;                         //Variável de iterações.
  while (sequencia[i] != '\0') {     //Enqunto não encontrar o caractere o nulo '\0'.
    brilhoSequencial(sequencia[i]);  //Chamando a função que cuida dos brilhos correspondentes para traço ou ponto.
    i++;                             //Posição do array +1.
  }                                  //Fim enquanto.

  delay(600);  //Tempo entre posições.
}  //Fim Função.

char brilhoSequencial(char pontoTraco) {  //Função para brilho do ponto ou traço.

  digitalWrite(led, HIGH);  //Ligar o led.

  if (pontoTraco == '.') {  //Se for um '.', ligar o led.
    delay(delayPonto);      //Tempo para ponto.
  } else {                  //Se for traço.
    delay(delayTraco);      //Tempo para traço.
  }
  digitalWrite(led, LOW);  //Desliga o led.
  delay(delayPonto);       //Tempo do led desligado.
  return pontoTraco;       //Retorno da função.
}  //Fim função.

void loop() {                    //Função para eventos.
  if (Serial.available() > 0) {  //Se for disponível a comunicação serial.

    letra = Serial.read();                //A variável "letra", recebe o que for digitado no terminal.
    if (letra >= 'a' && letra <= 'z') {   //Se a letra maior igual à 'a' e menor igual à 'c'.
      brilhoCodigo(codigo[letra - 'a']);  //Chamar função que percorre o array.
      Serial.print(codigo[letra - 'a']);  //Printando o código Morse de acordo com a letra ou a frase.
    }else if (letra >= 'A' && letra <= 'Z') {   //Se a letra maior igual à 'a' maiuscula e menor igual à 'c' maiuscula.
      brilhoCodigo(codigo[letra - 'A']);  //Chamar função que percorre o array.
      Serial.print(codigo[letra - 'A']);  //Printando o código Morse de acordo com a letra ou a frase.
    } 
    if (letra == ' ') {  //Senão, se for um espaço entre palavras?
      delay(800);               //Implicar um tempo de 800ms, entre as palavras.
    }

  }  //Fim se.
}  //Fim função.