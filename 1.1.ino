#include <Servo.h>

int pos = 0;
int pos1 = 0;

int R = 0;
int R1 = 0;

Servo servo_9;
Servo servo_6;

void setup()
{
  servo_9.attach(9, 500, 2500);
  servo_6.attach(6, 500, 2500);

  pinMode(A3, INPUT);  // Pot 1
  pinMode(A2, INPUT);  // Pot 2
}

void loop()
{
  R = analogRead(A3);
  R1 = analogRead(A2);

  pos = R / 6;
  pos1 = R1 / 6;

  servo_9.write(pos);
  servo_6.write(pos1);

  delay(150);
}
