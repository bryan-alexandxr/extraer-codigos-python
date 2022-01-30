#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

const int trig = 8;

const int echo = 6;

int duracion;

int distancia;

int personas = 0;

int boton = 3;

int estadodelboton = 0;

int sensordeagua ;


void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(4, OUTPUT);  
  pinMode(2, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(boton, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  sensordeagua = analogRead(A0);
  if (sensordeagua <400){

    lcd.setCursor(0,0);
    lcd.print("PERSONAS: ");
    lcd.setCursor(11,0);
    lcd.print(personas);
    lcd.setCursor(0,1);
    lcd.print("Alcohol: ");
    lcd.setCursor(9,1);
    lcd.print("VACIO");
    
    }
      
     else 
      { lcd.setCursor(0,0);
        lcd.print("PERSONAS: ");
        lcd.setCursor(11,0);
        lcd.print(personas);
        lcd.setCursor(0,1);
        lcd.print("Alcohol: ");
        lcd.setCursor(9,1);
        lcd.print("LLENO");
      }
  
 
}

void loop()
{
  
  
  digitalWrite(trig, LOW);
  delayMicroseconds (2);
  
  digitalWrite(trig, HIGH);
  delayMicroseconds (10);

  digitalWrite (trig, LOW);
  

  duracion = pulseIn(echo, HIGH);
  distancia = duracion/58.2;



  sensordeagua = analogRead(A0);

  if (distancia < 8 && sensordeagua >400)
  {
    personas = personas +1 ;
    delay (200);
 
    digitalWrite(4, HIGH);
    digitalWrite(2, HIGH);
    delay (180);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    delay(1000);
    if (sensordeagua <400){

    lcd.setCursor(0,0);
    lcd.print("PERSONAS: ");
    lcd.setCursor(11,0);
    lcd.print(personas);
    lcd.setCursor(0,1);
    lcd.print("Alcohol: ");
    lcd.setCursor(9,1);
    lcd.print("VACIO");
    
    } else 
      { lcd.setCursor(0,0);
        lcd.print("PERSONAS: ");
        lcd.setCursor(11,0);
        lcd.print(personas);
        lcd.setCursor(0,1);
        lcd.print("Alcohol: ");
        lcd.setCursor(9,1);
        lcd.print("LLENO");
      }
  

    
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("PERSONAS: ");
    lcd.setCursor(11,0);
    lcd.print(personas);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW); 
    if (sensordeagua <400){

    lcd.setCursor(0,0);
    lcd.print("PERSONAS: ");
    lcd.setCursor(11,0);
    lcd.print(personas);
    lcd.setCursor(0,1);
    lcd.print("Alcohol: ");
    lcd.setCursor(9,1);
    lcd.print("VACIO");
    
    } else 
      { lcd.setCursor(0,0);
        lcd.print("PERSONAS: ");
        lcd.setCursor(11,0);
        lcd.print(personas);
        lcd.setCursor(0,1);
        lcd.print("Alcohol: ");
        lcd.setCursor(9,1);
        lcd.print("LLENO");
      }
  }

  estadodelboton = digitalRead(boton);
  if(estadodelboton != 0)
  {
    sensordeagua = analogRead(A0);
    personas = 0; 
    lcd.clear();
    delay (200);
    if (sensordeagua <400){

    lcd.setCursor(0,0);
    lcd.print("PERSONAS: ");
    lcd.setCursor(11,0);
    lcd.print(personas);
    lcd.setCursor(0,1);
    lcd.print("Alcohol: ");
    lcd.setCursor(9,1);
    lcd.print("VACIO");
    
    } else 
      { lcd.setCursor(0,0);
        lcd.print("PERSONAS: ");
        lcd.setCursor(11,0);
        lcd.print(personas);
        lcd.setCursor(0,1);
        lcd.print("Alcohol: ");
        lcd.setCursor(9,1);
        lcd.print("LLENO");
      }
  }
}
