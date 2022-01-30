#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20, 16, 2);

const int trig = 8;
const int echo = 6;

int duracion;

int distancia;

int personas = 0;

int boton = 3;

int estadodelboton = 0;

int sensordeagua = A1;

int llenoVacio = 0;

int valorsensor = 9000; //Se usa este valor en simulacion para comprobar que funcione

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
  Serial.begin(9600);
}

void loop()
{

  digitalWrite(trig, LOW);
  delayMicroseconds (2);

  digitalWrite(trig, HIGH);
  delayMicroseconds (10);

  digitalWrite (trig, LOW);

  estadodelboton = digitalRead(boton);
  duracion = pulseIn(echo, HIGH);
  distancia = duracion / 58.2;

  //Este valor se obtiene del sensor, el cual no se simula correctamente por lo cual se establece valores arbitrarios para probar el funcionamiento
  //valorsensor = analogRead(sensordeagua);

  if (valorsensor > 8000)
  {
    lcd.setCursor(0, 1);
    lcd.print("Alcohol: ");
    lcd.setCursor(9, 1);
    lcd.print("LLENO");
    llenoVacio = 1;
  }

  if (valorsensor < 5000)
  {
    lcd.setCursor(0, 1);
    lcd.print("Alcohol: ");
    lcd.setCursor(9, 1);
    lcd.print("VACIO");
    Serial.println(0);
    llenoVacio = 0;
    delay(5000); //5 segundos - tiempo que puede ser modificado para enviar cada cierto tiempo la alerta de que no hay gel

  }

  if ((distancia < 8) && (llenoVacio == 1))
  {
    personas = personas + 1 ;
    delay (200);

    lcd.setCursor(0, 0);
    lcd.print("PERSONAS: ");
    lcd.setCursor(11, 0);
    lcd.print(personas);
    //se puede enviar la notificación a Telegram cada vez que alguien usa el dispositivo o enviar un reporte de cuanta gente lo usó
    //al final de cada día
    Serial.println(personas);
    digitalWrite(4, HIGH);
    digitalWrite(2, HIGH);
    delay (180);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    delay(1000);
    //cada vez que pasan la mano se gasta el gel hasta que ya se acaba y deja de funcionar a menos  de que se rellene
    valorsensor = valorsensor - 1000;
  }

  else
  {
    lcd.setCursor(0, 0);
    lcd.print("PERSONAS: ");
    lcd.setCursor(11, 0);
    lcd.print(personas);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
  }

  if (estadodelboton == HIGH)
  {
    //Al aplastar el botón se supone que se acaba el día, por lo cual se puede enviar un informe a Telegram del total
    //de personas  para llevar un registro y analizar en base a esto el comportamiento.
    //Serial.println(personas);

    personas = 0;
    lcd.clear();
    delay (200);
    lcd.setCursor(0, 0);
    lcd.print("PERSONAS: ");
    lcd.setCursor(11, 0);
    lcd.print(personas);
    lcd.setCursor(0, 1);
    lcd.print("Alcohol: ");
    lcd.setCursor(9, 1);
    lcd.print("LLENO");
    valorsensor = 9000; //se asume que al momento de limpiar el LCD, tambien se llena el tacho del gel - nuevo día
  }
}
