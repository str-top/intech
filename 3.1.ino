#include <Keypad.h>

#include <LiquidCrystal.h>

#include <Servo.h>

const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const byte ROWS = 4, COLS = 4;

char keyMap[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {0, 12, 11, 10};

byte colPins[COLS] = {9, 8, 7, 6};

Keypad keyPad = Keypad(makeKeymap(keyMap), rowPins, colPins, ROWS, COLS);


int pinRed   = 5;
int pinBlue  = 4;
int pinGreen = 3;

int pos = 0;

Servo servo;
int servoPin = 2;

const int
  ANGLE_OPEN = 0,
  ANGLE_CLOSE = 90;

enum States {
  NewCode,
  Armed,
  Lock,
  Unlock
};
States states;

const byte CODE_LEN = 4;
char codes[CODE_LEN] = {0};

void setup() {

  pinMode(pinRed,   OUTPUT);
  pinMode(pinBlue,  OUTPUT);
  pinMode(pinGreen, OUTPUT);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("** Code  lock **");

  lcd.setCursor(pos, 1);
  lcd.print("Ver. 1.0.0. 2024");

  servo.attach(servoPin);
  servo.write(ANGLE_OPEN);

  digitalWrite(pinBlue, HIGH);
  delay(1600);
  digitalWrite(pinBlue, LOW);

  lcd.clear();
  states = NewCode;
}

void loop() {

  switch(states) {
    case NewCode:
      newCode();
      break;
    case Armed:
      armed();
      break;
    case Lock:
      lock();
      break;
    case Unlock:
      unlock();
      break;
  }

  delay(100);
}


void newCode() {
  digitalWrite(pinGreen, HIGH);
  digitalWrite(pinRed, LOW);
  digitalWrite(pinBlue, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Enter code here:");
  lcd.setCursor(0, 1);
  lcd.print("           ____ ");

  lcd.cursor();

  for(byte pos = 0;pos < CODE_LEN; ++pos) {
    lcd.setCursor(11+pos, 1);
    char key;
    while (!(key = keyPad.getKey()));
    codes[pos] = key;
    lcd.print(char(0));
  }

  lcd.noCursor();
  states = Armed;
}


void armed() {
  digitalWrite(pinGreen, HIGH);
  digitalWrite(pinRed, LOW);
  digitalWrite(pinBlue, LOW);

  lcd.noCursor();
  lcd.setCursor(0, 0);
  lcd.print("Now is opened   ");

  lcd.setCursor(0, 1);
  lcd.print("Press * to close");


  char key;
  while(!(key = keyPad.getKey())) {
    if (key == '*' || key == 'C') break;
  }
  states = key == '*'?Lock:NewCode;
}


void lock() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Locking...");


  servo.write(ANGLE_CLOSE);
  digitalWrite(pinGreen, LOW);
  digitalWrite(pinRed, HIGH);
  digitalWrite(pinBlue, LOW);
  delay(500);


  lcd.setCursor(0, 0);
  lcd.print("Lock. To open   ");

  lcd.setCursor(0, 1);
  lcd.print("press # than cod");


  char key;
  while(true) {
    while(!(key = keyPad.getKey()));


    if (key == '#') {
      states = Unlock;
      break;
    }
  }

}


void unlock() {

  digitalWrite(pinGreen, HIGH);
  digitalWrite(pinRed, HIGH);
  digitalWrite(pinBlue, LOW);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter code: ____");
  lcd.cursor();


  for(byte pos = 0; pos < CODE_LEN; ++pos) {

    lcd.setCursor(12 + pos, 0);


    char key;
    while(!(key = keyPad.getKey()));
    lcd.print(char(0));


    if (key != codes[pos]) {

      digitalWrite(pinRed, HIGH);
      digitalWrite(pinGreen, LOW);
      digitalWrite(pinBlue, LOW);


      lcd.noCursor();


      lcd.setCursor(0, 1);
      lcd.print("Wrong code, lock");


      delay(1900);
      states = Lock;
      return;
    }
  }


  lcd.noCursor();

  servo.write(ANGLE_OPEN);

  states = Armed;
}
