#include <Servo.h> // объявление библиотеки Servo с расширением h

#define VCC A0 // объявление переменных
#define MOTOR 8
#define TEMP A1
#define SIG A2
#define SER 9

Servo ser;

void setup() { // начало цикла setup, выполняющегося один раз перед началом программы

  Serial.begin(9600); // обмен данными платы arduino с компьютером на скорости 9600 бод
  pinMode(MOTOR, OUTPUT); // объявление режимов работы всех пинов
  pinMode(VCC, OUTPUT);
  pinMode(SIG, INPUT);
  pinMode(TEMP, INPUT);

  ser.attach(SER);


}

void loop() { // начало бесконечного цикла loop

  digitalWrite(VCC, HIGH); // включение датчика влажности почвы
  int sigVal = analogRead(SIG); // чтение значения с датчика влажности почвы в переменную sigVal
  int tempVal = analogRead(TEMP); // чтение значения с датчика температуры в переменную tempVal
  Serial.print(sigVal); // вывод значений с датчиков влажности почвы и температуры
  Serial.print(" || ");
  Serial.println(tempVal);
  digitalWrite(VCC, LOW);// выключение датчика влажности почвы для предотвращения его разложения в почве

  if (tempVal < 140) { // условие работы датчика температуры
	ser.write(0);
  } else if (tempVal > 150) {
    ser.write(45); // поворот сервопривода (форточки) на 45 градусов
  }


  if (sigVal < 300) { // условие работы датчика влажности почвы
    digitalWrite(MOTOR, HIGH); // включение мотора (насоса)
  } else {
    digitalWrite(MOTOR, LOW); // включение мотора (насоса)
  }
  digitalWrite(VCC, LOW); // выключение датчика влажности почвы
  delay(100); // задержка 100 мс
}
