#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo servo;

int hours = 0, minutes = 0, seconds = 0;
int shours = 0, sminutes = 0, sseconds = 0;

int time = 0;
int eatStatus = 1;
int eatTime = 0;

void LCDdisplay() {
  lcd.clear();

  if (hours < 10) lcd.print("0");
  lcd.print(hours);
  lcd.print(":");

  if (minutes < 10) lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");

  if (seconds < 10) lcd.print("0");
  lcd.print(seconds);
}

void add(int t) {
  if (t == 0) {
    seconds++;
    if (seconds >= 60) seconds = 0;
  } else if (t == 1) {
    minutes++;
    if (minutes >= 60) minutes = 0;
  } else if (t == 2) {
    hours++;
    if (hours >= 25) hours = 0;
  }
}

void sub(int t) {
  if (t == 0) {
    seconds--;
    if (seconds < 0) seconds = 59;
  } else if (t == 1) {
    minutes--;
    if (minutes < 0) minutes = 59;
  } else if (t == 2) {
    hours--;
    if (hours < 0) hours = 24;
  }
}

void timeToEat() {
  tone(0, 700, 500);
  lcd.clear();
  lcd.print("FEEDER OPEN");
  servo.write(90);
  delay(3000);
  servo.write(0);
}

void setup() {
  lcd.begin(16, 2);
  LCDdisplay();

  servo.attach(6);
  servo.write(0);

  pinMode(1, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
}

void loop() {
  if (digitalRead(1) && eatStatus) {
    timeToEat();
    eatStatus = 0;
  }

  if (digitalRead(8)) {
    time++;
    if (time >= 3) time = 0;
  }

  if (digitalRead(9)) {
    add(time);
    LCDdisplay();
  }

  if (digitalRead(10)) {
    sub(time);
    LCDdisplay();
  }

  if (digitalRead(7)) {
    shours = hours;
    sminutes = minutes;
    sseconds = seconds;

    while (true) {
      if (digitalRead(1) && eatStatus) {
        timeToEat();
        eatStatus = 0;
      }

      if (!eatStatus) eatTime++;

      if (eatTime >= 600) {
        eatStatus = 1;
        eatTime = 0;
      }

      delay(1000);

      seconds--;
      if (seconds < 0) {
        if (minutes > 0 || hours > 0) seconds = 59;
        else seconds = 0;
        minutes--;
      }

      if (minutes < 0) {
        if (hours > 0) minutes = 59;
        else minutes = 0;
        hours--;
      }

      if (hours < 0) {
        hours = shours;
        minutes = sminutes;
        seconds = sseconds;
        timeToEat();
      }

      LCDdisplay();

      if (digitalRead(7)) break;
    }
  }

  if (!eatStatus) eatTime++;

  if (eatTime >= 6000) {
    eatStatus = 1;
    eatTime = 0;
  }

  delay(100);
}
