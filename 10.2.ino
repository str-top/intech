#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#define triggerPin 13
#define ehoSignal 12

#define buzzer 9

#define btn 2

#define move A2

#define ledPin  10
#define NUMPIXELS 4


#define button 2

#define TMP A0

int gas = A1;
int gmax = 550;

int raw = 0;
float temp = 0;

int signalising = 0;


LiquidCrystal lcd(8,7,6,5,4,3);
Servo servo;
Adafruit_NeoPixel strip (NUMPIXELS, ledPin, NEO_GRB + NEO_KHZ800);

void setup()
{
  lcd.begin(16, 2);
  strip.begin();
  strip.setBrightness(100);
  pinMode(button, INPUT_PULLUP);
  pinMode(triggerPin, OUTPUT);
  pinMode(ehoSignal, INPUT);
  servo.attach(11);

  pinMode(move, INPUT);

  pinMode(gas, INPUT);

  Serial.begin(9600);
  pinMode( A0, INPUT );
}

int doCheck()
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  int t = pulseIn(ehoSignal, HIGH);
  int s = (t * 0.035) / 2;
  return s;
}

void doorOpen()
{
  strip.setPixelColor(0, strip.Color(0, 255, 0));
  strip.setPixelColor(1, strip.Color(0, 255, 0));
  strip.setPixelColor(2, strip.Color(0, 255, 0));
  strip.setPixelColor(3, strip.Color(0, 255, 0));
  strip.show();
  lcd.setCursor(0, 1);
  lcd.print("Door Opened");
}

void doorClose()
{
  strip.setPixelColor(0, strip.Color(0, 0, 0));
  strip.setPixelColor(1, strip.Color(0, 0, 0));
  strip.setPixelColor(2, strip.Color(0, 0, 0));
  strip.setPixelColor(3, strip.Color(0, 0, 0));
  strip.show();
}

void loop()
{
  if(digitalRead(btn) == 1)
  {
    if(signalising == 0)
    {
      signalising = 1;
      lcd.setCursor(0, 1);
      lcd.print("Signal On");
      return;
    }
    if(signalising == 1)
    {
      signalising = 0;
      lcd.setCursor(0, 1);
      lcd.print("Signal Off");
      return;
    }

  }
  int sm = doCheck();
  if(sm < 50)
  {
    servo.write(90);
    doorOpen();
  }
  if(sm > 50 && sm < 100)
  {
    servo.write(0);
    doorClose();
  }
  if(digitalRead(move) == 1)
  {
    if(signalising == 1)
    {
      lcd.setCursor(0, 1);
      lcd.print("Something moving");
      strip.setPixelColor(0, strip.Color(255, 0, 0));
      strip.setPixelColor(1, strip.Color(255, 0, 0));
      strip.setPixelColor(2, strip.Color(225, 0, 0));
      strip.setPixelColor(3, strip.Color(255, 0, 0));
      strip.show();
      tone(buzzer,100);
      delay(100);
      noTone(buzzer);
      strip.setPixelColor(0, strip.Color(0, 0, 0));
      strip.setPixelColor(1, strip.Color(0, 0, 0));
      strip.setPixelColor(2, strip.Color(0, 0, 0));
      strip.setPixelColor(3, strip.Color(0, 0, 0));
      strip.show();
    }
  }

  checkTemp();
  checkGas();

}

void checkTemp()
{
  raw = analogRead(A0);
   float voltage = raw * 5.0;
   voltage /= 1024.0;
   float temperatureC = (voltage - 0.5) * 100 ;
   lcd.setCursor(0, 0);
   lcd.print("Temp:");
   lcd.print(temperatureC);
   lcd.print("c");
   delay(500);
   lcd.clear();
}

void checkGas()
{
  int gasly = analogRead(gas) - 306;
  lcd.setCursor(0, 1);
  lcd.print("Gas:");
  lcd.print(gasly);
  if( gasly > 5 && gasly < 60)
  {
      strip.setPixelColor(0, strip.Color(0, 255, 0));
      strip.setPixelColor(1, strip.Color(0, 255, 0));
      strip.setPixelColor(2, strip.Color(0, 255, 0));
      strip.setPixelColor(3, strip.Color(0, 255, 0));
      strip.show();
    delay(100);
  }
  if( gasly > 60 && gasly < 100)
  {
      strip.setPixelColor(0, strip.Color(0, 255, 255));
      strip.setPixelColor(1, strip.Color(0, 255, 255));
      strip.setPixelColor(2, strip.Color(0, 255, 255));
      strip.setPixelColor(3, strip.Color(0, 255, 255));
      strip.show();
      delay(100);
  }
  if( gasly > 100)
  {
      strip.setPixelColor(0, strip.Color(255, 0, 0));
      strip.setPixelColor(1, strip.Color(255, 0, 0));
      strip.setPixelColor(2, strip.Color(225, 0, 0));
      strip.setPixelColor(3, strip.Color(255, 0, 0));
      strip.show();
      tone(buzzer,200);
      delay(100);
      noTone(buzzer);
  }
}
