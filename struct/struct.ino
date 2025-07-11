#include <string.h>
struct FichaAluno {
  String nome="Manoel";
  char disciplina[30];
  float notaProva1, notaProva2;
};
void setup() {
  // put your setup code here, to run once:
  struct FichaAluno Aluno;
  Serial.begin(9600);
  Serial.println("------------ Cadastro de alunos ----------");
  Serial.print("Nome aluno: ");
  Serial.println(Aluno.nome);
  Serial.print(Aluno.disciplina);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
