#include "LiquidCrystal.h"
#define PIN_LEDb 13
char data[10][10];
LiquidCrystal lcd(11,10,5,4,3,2);
void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LEDb,OUTPUT);
  digitalWrite(PIN_LEDb,LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    int i,j;
    for(i=0;i<100;i++)
    {
      for(j=0;j<100;j++)
      {
      data[i][j]=Serial.read();
      }
    }
    
  }
  if(data!="")
  {
    digitalWrite(PIN_LEDb,HIGH);
    int i,j;
    for(i=0;i<100;i++)
    {
      for(j=0;j<100;j++)
      {
        lcd.begin(10,2);//la taille du lcd
        lcd.print(data[i][j]);
        delay(50000);
      //sprintf(data[i][j],%s %s);
      }
    }
    
    Serial.write('1');
  }
  else
  {
    digitalWrite(PIN_LEDb,HIGH);
    Serial.write('0');
  }
}
