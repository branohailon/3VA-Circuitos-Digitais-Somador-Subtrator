// include the library code:
#include <LiquidCrystal.h>
#include <math.h>
#include <string.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define Dip1D 6
#define Dip2D 7
#define Dip3D 8
#define Dip4D 9
#define Dip1E A1
#define Dip2E 1
#define Dip3E 10
#define Dip4E 13
#define Dip0 A0

int Cin = 0;
int Cout = 0;
int Cout4 = 0;
int Cout3 = 0;
int Cout2 = 0;
int Cout1 = 0;
int saida4 = 0;
int saida3 = 0;
int saida2 = 0;
int saida1 = 0;
int saida = 0;

void setup() {
  pinMode(Dip1D, INPUT_PULLUP);
  pinMode(Dip2D, INPUT_PULLUP);
  pinMode(Dip3D, INPUT_PULLUP);
  pinMode(Dip4D, INPUT_PULLUP);
  pinMode(Dip1E, INPUT_PULLUP);
  pinMode(Dip2E, INPUT_PULLUP);
  pinMode(Dip3E, INPUT_PULLUP);
  pinMode(Dip4E, INPUT_PULLUP);
  pinMode(Dip0,  INPUT_PULLUP);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);  
}

//FUNÇÃO PARA TRANSFORMAR BINARIO EM DECIMAL
int funcaoDecimal(int binario){
  int decimal=0,d=1;
   do{
    decimal = decimal+(binario%10)*d;
    d = d*2;
    binario = binario/10;
  }while(binario!=0);
  return decimal;
}

void loop() {

  int Dip1EStatus = digitalRead(Dip1E);
  int Dip2EStatus = digitalRead(Dip2E);
  int Dip3EStatus = digitalRead(Dip3E);
  int Dip4EStatus = digitalRead(Dip4E);
  int Dip0Status  = digitalRead(Dip0);
  int Dip1DStatus = digitalRead(Dip1D);
  int Dip2DStatus = digitalRead(Dip2D);
  int Dip3DStatus = digitalRead(Dip3D);
  int Dip4DStatus = digitalRead(Dip4D);
  
  //SAIDA dip4
  saida4 = ((Dip4EStatus && !Dip4DStatus && !Cin) + (!Dip4EStatus && !Dip4DStatus && Cin) + (Dip4EStatus && Dip4DStatus && Cin) + (!Dip4EStatus && Dip4DStatus && !Cin));
  //COUT dip4
  Cout4 = ((Dip4DStatus && Cin)||(!Dip0Status && Dip4EStatus && Dip4DStatus)||(!Dip0Status && Dip4EStatus && Cin)||(Dip0Status && !Dip4EStatus && Dip4DStatus)||(Dip0Status && !Dip4EStatus && Cin));

  //SAIDA dip3
  saida3 = ((Dip3EStatus && !Dip3DStatus && !Cout4) + (!Dip3EStatus && !Dip3DStatus && Cout4) + (Dip3EStatus && Dip3DStatus && Cout4) + (!Dip3EStatus && Dip3DStatus && !Cout4));
  //COUT dip3
  Cout3 = ((Dip3DStatus && Cout4)||(!Dip0Status && Dip3EStatus && Dip3DStatus)||(!Dip0Status && Dip3EStatus && Cout4)||(Dip0Status && !Dip3EStatus && Dip3DStatus)||(Dip0Status && !Dip3EStatus && Cout4));

  //SAIDA dip2
  saida2 = ((Dip2EStatus && !Dip2DStatus && !Cout3) + (!Dip2EStatus && !Dip2DStatus && Cout3) + (Dip2EStatus && Dip2DStatus && Cout3) + (!Dip2EStatus && Dip2DStatus && !Cout3));
  //COUT dip2
  Cout2 = ((Dip2DStatus && Cout3)||(!Dip0Status && Dip2EStatus && Dip2DStatus)||(!Dip0Status && Dip2EStatus && Cout3)||(Dip0Status && !Dip2EStatus && Dip2DStatus)||(Dip0Status && !Dip2EStatus && Cout3));

  //SAIDA dip1
  saida1 = ((Dip1EStatus && !Dip1DStatus && !Cout2) + (!Dip1EStatus && !Dip1DStatus && Cout2) + (Dip1EStatus && Dip1DStatus && Cout2) + (!Dip1EStatus && Dip1DStatus && !Cout2));
  //COUT dip1
  Cout1 = ((Dip1DStatus && Cout2)||(!Dip0Status && Dip1EStatus && Dip1DStatus)||(!Dip0Status && Dip1EStatus && Cout2)||(Dip0Status && !Dip1EStatus && Dip1DStatus)||(Dip0Status && !Dip1EStatus && Cout2));

  //SAIDA
  saida = ((!Dip1EStatus && Dip1DStatus && !Cout1 && !Dip0Status) + (Dip1EStatus && !Dip1DStatus && !Cout1 && !Dip0Status) + (!Dip1EStatus && !Dip1DStatus && !Cout1 && Dip0Status) + (Dip1EStatus && Dip1DStatus && !Cout1 && Dip0Status) + (!Dip1EStatus && Dip1DStatus && Cout1 && Dip0Status) + (Dip1EStatus && !Dip1DStatus && Cout1 && Dip0Status) + (Dip1EStatus && Dip1DStatus && Cout1 && !Dip0Status) + (!Dip1EStatus && !Dip1DStatus && Cout1 && !Dip0Status));
  //COUT
  Cout = ((Dip1DStatus && Cout1)||(!Dip0Status && Dip1EStatus && Dip1DStatus)||(!Dip0Status && Dip1EStatus && Cout1)||(Dip0Status && !Dip1EStatus && Dip1DStatus)||(Dip0Status && !Dip1EStatus && Cout1));

  //CONVERTE DIP A PARA CHAR
  char Dip1EStatusS[5]; sprintf(Dip1EStatusS, "%i",Dip1EStatus);
  char Dip2EStatusS[5]; sprintf(Dip2EStatusS, "%i",Dip2EStatus);
  char Dip3EStatusS[5]; sprintf(Dip3EStatusS, "%i",Dip3EStatus);
  char Dip4EStatusS[5]; sprintf(Dip4EStatusS, "%i",Dip4EStatus);
  //CONVERTE A ENTRADA DIP A PARA STRING AUXILIAR
  char auxiliarDipA[256];
  sprintf(auxiliarDipA, "%s%s%s%s", Dip1EStatusS, Dip2EStatusS, Dip3EStatusS,Dip4EStatusS);
  //CONVERTE STRING PARA INTEIRO
  int DipA = atoi(auxiliarDipA);

  //CONVERTE DIP B PARA CHAR
  char Dip1DStatusS[5]; sprintf(Dip1DStatusS, "%i",Dip1DStatus);
  char Dip2DStatusS[5]; sprintf(Dip2DStatusS, "%i",Dip2DStatus);
  char Dip3DStatusS[5]; sprintf(Dip3DStatusS, "%i",Dip3DStatus);
  char Dip4DStatusS[5]; sprintf(Dip4DStatusS, "%i",Dip4DStatus);
  //CONVERTE A ENTRADA DIP B PARA STRING AUXILIAR
  char auxiliarDipB[256];
  sprintf(auxiliarDipB, "%s%s%s%s", Dip1DStatusS, Dip2DStatusS, Dip3DStatusS,Dip4DStatusS);
  //CONVERTE STRING PARA INTEIRO
  int DipB = atoi(auxiliarDipB); 
  
  //CONVERTE PARA CHAR AS SAIDAS
  char CoutS[5];   sprintf(CoutS, "%i",Cout);
  char saida1S[5]; sprintf(saida1S, "%i",saida1);
  char saida2S[5]; sprintf(saida2S, "%i",saida2);
  char saida3S[5]; sprintf(saida3S, "%i",saida3);
  char saida4S[5]; sprintf(saida4S, "%i",saida4);
  //CONVERTE AS SAIDAS PARA STRING AUXILIAR
  char auxiliar[256];
  sprintf(auxiliar, "%s%s%s%s%s", CoutS, saida1S, saida2S,saida3S,saida4S);
  //CONVERTE STRING PARA INTEIRO
  int resultado = atoi(auxiliar);
   
  //MOSTRA NO DISPLAY LCD
  lcd.setCursor(0, 0);
  lcd.print(funcaoDecimal(DipA));
  //se for 0 vira + se for 1 vira-
  if(Dip0Status == 0){lcd.print(" + ");}else if(Dip0Status == 1){lcd.print(" - ");}
  lcd.print(funcaoDecimal(DipB));
  lcd.setCursor(0, 1);  
  //delay para limpar resultado da tela
   lcd.print(funcaoDecimal(resultado));
   delay(5000);
   lcd.clear();
   delay(2000);   
}


