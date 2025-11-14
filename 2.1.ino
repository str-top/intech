#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int sensor = A0;
float sensorvalue = 0;
int a = A1;

void setup() {
  lcd.begin(16, 2);
  Wire.begin();
}

void loop() {
  sensorvalue = analogRead(sensor);
  float light = analogRead(a);

  lcd.setCursor(0,0);
  lcd.print("                "); 
  lcd.setCursor(0,0);

  if (light > 800){
    lcd.print("Temnovato");
  }
  else if (light < 500){
    lcd.print("Solnechno");
  }

  float voltage = sensorvalue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100;

  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.setCursor(5, 1);
  lcd.print(temperature);

  delay(500);
}
