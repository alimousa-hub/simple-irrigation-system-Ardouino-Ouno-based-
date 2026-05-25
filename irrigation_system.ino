#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);
#include <Servo.h>
Servo servo ;
#define soil A3
#define  pushb 7 
#define  motor 2
#define  LDR A2
#define red 3
#define yellow 4
#define green 5
#define servom 10
#define LED 8
int buttonPin = 6;
int seconds = 0;
int valueLDR;
int valuesoil;
int psoil;
int pLDR;
int lcdLDR;
int counteron=1;
int counteroff=1;
int buttonState;
int temp;
int templcd;
//setup
//===========================
void setup(){
servo.attach(servom);
servo.attach(servom, 0, 180)  ;
  pinMode(green,OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  pinMode(pushb,INPUT);
  pinMode(motor,OUTPUT);
 
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(servom,OUTPUT);
  pinMode(LED,OUTPUT);
  lcd.begin(16, 2);
  lcd.print("system ON");
  delay(1000);
  lcd.clear();
  lcd.print("initializing");
  lcd.setCursor(0,1);
  lcd.print("reading data");
  delay(3000);
  lcd.clear();
  lcd.print("moisture%:");
  lcd.setCursor(0,1);
  lcd.print("bright%:");
  
}
//loooppp
//===================================================
void loop()
{
  
  delay(500);
  valuesoil = analogRead(soil);
  valueLDR =analogRead(LDR); 
 psoil=map(valuesoil,0,876,0,99);
pLDR=map(valueLDR,344,1017,0,99);
lcdLDR=map(pLDR,0,100,99,0);  
 
  lcd.setCursor(11,0);
  lcd.print(psoil);
  lcd.setCursor(8,1);
   lcd.print(lcdLDR);
 buttonState = digitalRead(buttonPin);  
 
    checkButton();
  
  
  
  if (psoil>=70){
   greenON();
    redOFF();
    yellowOFF();
  }
  else if (psoil<70&&psoil>=30){
   greenOFF();
    redOFF();
    yellowON();
  }
  else if (psoil<30){
   greenOFF();
    redON();
    yellowOFF();
   water();
  }
  //brightness control 
//-------------
  if (pLDR>=40){
  brightnessON();
   lcd.setCursor(10,1);
    lcd.print("LEDON");
    
  }
  
  else{
    
    brightnessOFF();
     lcd.setCursor(10,1);
    lcd.print("     ");
  }

  
 
}
//===valve==========
//-----------------------
void openvalve(){
 servo.write(0); 
}
void closevalve(){
  
servo.write(90); 

}
//functions==========================================================
//-------------------------
//======pump======
//-------------------------
void pumpON(){
  digitalWrite(motor,HIGH);
}
void pumpOFF(){
  digitalWrite(motor,LOW);
}
//---------------------------
//=====LEDsss=================
//--------------------------------------------
void greenON(){
  digitalWrite(green,HIGH);
  
}
void greenOFF(){
 digitalWrite(green,LOW); 
}
//===============================
void yellowON(){
  digitalWrite(yellow,HIGH);
  
}
void yellowOFF(){
 digitalWrite(yellow,LOW); 
}
//============================
void redON(){
  digitalWrite(red,HIGH);
  
}
void redOFF(){
 digitalWrite(red,LOW); 
}
//------------------------------------------------------
//======brightness====
void brightnessON(){
 digitalWrite(LED,HIGH); 
}
void brightnessOFF(){
 digitalWrite(LED,LOW); 
}

//water------------------------------


void water(){
  lcd.clear();
  openvalve();
  pumpON();
  
  lcd.print("watering%:");
 
 while (psoil<=90){
   lcd.setCursor(10,0);
    
  lcd.print(psoil);
 lcd.setCursor(12,0);
 lcd.print("    ");  
    delay(750);
  valuesoil=analogRead(soil);  
  psoil=map(valuesoil,0,876,0,100);  
 
   if (psoil>=70){
   greenON();
   redOFF();
   yellowOFF();
  }
    
  else if (psoil<70&&psoil>=30){
  greenOFF();
  redOFF();
  yellowON();
  }
    
  else if (psoil<30){
  greenOFF();
  redON();
  yellowOFF();
    
  }  
 lcd.write(psoil);
  }
  closevalve();
  pumpOFF();
  lcd.clear();
   lcd.print("moisture%:");
  lcd.setCursor(0,1);
  lcd.print("bright%:");
}
//checj bottum function 
void checkButton() {
  temp=0;
templcd=1;
  while (buttonState == HIGH) {   // button pressed
    if(templcd>0){
    lcd.clear();
    
      lcd.print("watering%:");
    templcd=0;
    }
     lcd.setCursor(10,0);    
     lcd.print(psoil);
     pumpON();
     openvalve();
    temp++;
    buttonState=digitalRead(6);
  } 
  
  if (temp>0){
    pumpOFF();
    openvalve();  
    closevalve();
    lcd.clear();
   lcd.print("moisture%:");
  lcd.setCursor(0,1);
  lcd.print("bright%:");
  
      }
}  
