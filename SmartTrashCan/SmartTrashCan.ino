#include <HCSR04.h>
#include <LiquidCrystal.h> // inclui a biblioteca para uso do Display LCD
// inicializa um objeto nos pinos para acesso as funções do LCD
const int RS = 13, EN = 12, D4 = 11, D5 = 10, D6 = 9, D7 = 8;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

UltraSonicDistanceSensor distanceSensor(7, 6);  // Inicia o sensor usando as portas digitais 13(trigger) e 12(echo)

const int buzzer = 2;

void setup(){
  // Configura o LCD com os número de colunas e linhas
  lcd.begin(16, 2); // 16 colunas e 2 linhas

  // Limpa o LCD
  lcd.clear();
  Serial.begin(9600);
  pinMode(5, OUTPUT); // verde
  pinMode(4, OUTPUT); // amarelo
  pinMode(3, OUTPUT); // vermelho
  pinMode(buzzer, OUTPUT); // Buzzer
}

void loop(){
   float distancia = distanceSensor.measureDistanceCm();
   float porcent = distancia/60*100;

  // posiciona o cursor do LCD
  lcd.setCursor(0, 0); // (coluna 0, linha 2)
  lcd.print("Estou com :"); // Imprime mensagem
  // posiciona o cursor do LCD
  lcd.setCursor(0, 1); // (coluna 0, linha 2)
  lcd.print(porcent); // Imprime mensagem
  // posiciona o cursor do LCD
  lcd.setCursor(5, 1); // (coluna 0, linha 2)
  lcd.print("% livre :)"); // Imprime mensagem

  // Buzzer para quando estiver abaixo de 10%

  if (porcent < 10){
    //Ligando o buzzer com uma frequencia de 1500 hz.
    tone(buzzer,1500);   
    delay(100);
   
    //Desligando o buzzer.
    noTone(buzzer);
    delay(100); 
  }

  // Leds piscadores
  
    
 
  if(porcent < 15){
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    delay(300);
    digitalWrite(3, LOW);
    delay(300);
  }
  else if (porcent >= 15 && porcent <= 40){
    digitalWrite(5, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
  }
  else if (porcent > 40 && porcent <= 100){
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
  }
  else if (porcent > 100){
    digitalWrite(5, HIGH);
    delay(300);
    digitalWrite(5, LOW);
    delay(300);
    digitalWrite(4, HIGH);
    delay(300);
    digitalWrite(4, LOW);
    delay(300);
    digitalWrite(3, HIGH);
    delay(300);
    digitalWrite(3, LOW);
    delay(300);
  }
}
