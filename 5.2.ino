#include <LiquidCrystal.h>
#define zoomer 3
#define tempsensor A0
uint32_t now = millis();
int const PIN_SGAS = A1;
int LED1 = 7;
int LED2 = 6;
int LED3 = 5;
int LED4 = 4;

int pot = A0;
float result = 0.0;

LiquidCrystal lcd(13, 12, 8, 9, 10,  11);


void setup(){
   pinMode(pot, INPUT);
  lcd.begin(16, 2);
  lcd.print("Temperature/dim");

  	pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(zoomer, OUTPUT);
    Serial.begin(9600);
}

void loop(){


   result = analogRead(pot);

  lcd.setCursor(0, 1);

  lcd.print((result*0.49)-50);
   delay(100);

  result = analogRead(PIN_SGAS);

  lcd.setCursor(7, 10);

  lcd.print((result));
   delay(100);

    int valor = analogRead(PIN_SGAS);
    valor = map(valor, 300, 750, 0, 100);
    digitalWrite(LED1, HIGH);
  	if (valor >= 30)
    {
      digitalWrite(LED2, HIGH);
      digitalWrite(zoomer, HIGH);
      delay(100);
      digitalWrite(zoomer, LOW);
      delay(100);
    }
     else
     {
       digitalWrite(LED2, LOW);
       digitalWrite(zoomer, LOW);
     }

  if (valor >= 50)
    {
      digitalWrite(LED3, HIGH);
      digitalWrite(zoomer, HIGH);
      delay(5);
      digitalWrite(zoomer, LOW);
      delay(5);
    }
     else
     {
       digitalWrite(LED3, LOW);
       digitalWrite(zoomer, LOW);
     }


    if (valor >= 80)
    {
      digitalWrite(LED4, HIGH);
      digitalWrite(zoomer, HIGH);
      delay(1);
      digitalWrite(zoomer, LOW);
      delay(1);
    }
     else
     {
       digitalWrite(LED4, LOW);
       digitalWrite(zoomer, LOW);
     }

  delay(250);
}
