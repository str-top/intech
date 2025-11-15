#include <Servo.h>

Servo servo_9;
Servo servo_6;

void setup()
{
  servo_9.attach(9, 500, 2500);
  servo_6.attach(6, 500, 2500);

  pinMode(A3, INPUT);  // Y axis
  pinMode(A2, INPUT);  // X axis
}

void loop()
{
  int R = analogRead(A3);
  int R1 = analogRead(A2);

  // convert joystick 0–1023 to servo angle 0–180
  int pos  = map(R, 0, 1023, 0, 180);
  int pos1 = map(R1, 0, 1023, 0, 180);

  servo_9.write(pos);
  servo_6.write(pos1);

  delay(20);
}
