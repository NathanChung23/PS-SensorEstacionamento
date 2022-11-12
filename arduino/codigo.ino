#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define col 16
#define lin  2
#define ende  0x20
#define verde1  4
#define vermelho1  5
#define verde2  10
#define vermelho2  11

int PinTrigger1 = 3;
int PinEcho1 = 2;
int PinTrigger2 = 13;
int PinEcho2 = 12;
float TempoEcho1 = 0;
float TempoEcho2 = 0;
bool vaga1 = false;
bool vaga2 = false;

const float VelocidadeSom_mporus = 0.000340;

LiquidCrystal_I2C lcd(ende,col,lin);

void setup()
{
  pinMode(PinTrigger1, OUTPUT);
  digitalWrite(PinTrigger1, LOW);
  pinMode(PinTrigger2, OUTPUT);
  digitalWrite(PinTrigger2, LOW);
  pinMode(verde1, OUTPUT);
  pinMode(vermelho1, OUTPUT);
  pinMode(verde2, OUTPUT);
  pinMode(vermelho2, OUTPUT);
  pinMode(PinEcho1, INPUT);
  pinMode(PinEcho2, INPUT);
  
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  delay(100);
  lcd.setCursor(0,0);
  lcd.print("Estacionamento");
  lcd.setCursor(0,1);
  lcd.print("FIAP 2022");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Vagas Livres");
  lcd.setCursor(0,1);
  lcd.print("Vagas Ocupadas");
}

void DisparaPulsoUltrassonico1(){
  digitalWrite(PinTrigger1, HIGH);
  delayMicroseconds(10);
  digitalWrite(PinTrigger1, LOW);
}

void DisparaPulsoUltrassonico2(){
  digitalWrite(PinTrigger2, HIGH);
  delayMicroseconds(10);
  digitalWrite(PinTrigger2, LOW);
}

float CalculaDistancia(float tempo_us){
  return((tempo_us*VelocidadeSom_mporus)/2);
}

void loop() 
{
  DisparaPulsoUltrassonico1();
  TempoEcho1 = pulseIn(PinEcho1, HIGH);
  DisparaPulsoUltrassonico2();
  TempoEcho2 = pulseIn(PinEcho2, HIGH);
  
  if (CalculaDistancia(TempoEcho1) <= 2){
    digitalWrite(verde1, LOW);
    digitalWrite(vermelho1, HIGH);
    vaga1 = true;
  } else {
    digitalWrite(vermelho1, LOW);
  	digitalWrite(verde1, HIGH);
    vaga1 = false;
  }
  
  
  
  if (CalculaDistancia(TempoEcho2) <= 2){
    digitalWrite(verde2, LOW);
    digitalWrite(vermelho2, HIGH);
    vaga2 = true;
  } else {
    digitalWrite(vermelho2, LOW);
  	digitalWrite(verde2, HIGH);
    vaga2 = false;
  }
  
  if (vaga1 && vaga2){
  	lcd.setCursor(15,1);
  	lcd.print("2");
    lcd.setCursor(15,0);
  	lcd.print("0");
  } else if (!vaga1 && !vaga2) {
    lcd.setCursor(15,0);
  	lcd.print("2");
    lcd.setCursor(15,1);
  	lcd.print("0");
  } else if (!vaga1 && vaga2) {
    lcd.setCursor(15,0);
  	lcd.print("1");
    lcd.setCursor(15,1);
  	lcd.print("1");
  } else {
    lcd.setCursor(15,0);
  	lcd.print("1");
    lcd.setCursor(15,1);
  	lcd.print("1");
  }
}
