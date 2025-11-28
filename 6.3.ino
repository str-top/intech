#include <Servo.h>

int Napr = 0;

int Vl = 0;

Servo servo_3;

void setup()
{
  pinMode(A1, INPUT);
  Serial.begin(9600);
  servo_3.attach(3, 500, 2500);
}

void loop()
{
  Vl = analogRead(A1);
  Serial.println(Vl);
  if (Vl < 200) {
    servo_3.write(90);
  } else {
    servo_3.write(0);
  }
  delay(10); // Delay a little bit to improve simulation performance
}
