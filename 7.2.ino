// C++ code
//
int Temp = 0;

int Ligt = 0;

int Water = 0;

int i = 0;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(A2, INPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  Temp = (-40 + 0.488155 * (analogRead(A0) - 20));
  Water = analogRead(A2);
  if (Temp >= 26) {
    digitalWrite(8, HIGH);
    digitalWrite(10, HIGH);
  } else {
    digitalWrite(8, LOW);
    digitalWrite(10, LOW);
  }
  if (Temp <= 23) {
    digitalWrite(7, HIGH);
    digitalWrite(11, HIGH);
  } else {
    digitalWrite(7, LOW);
    digitalWrite(11, LOW);
  }
  if (Water < 165) {
    digitalWrite(4, HIGH);
    digitalWrite(6, HIGH);
  } else {
    digitalWrite(4, LOW);
    digitalWrite(6, LOW);
  }
  Serial.print("Temp -");
  Serial.print(Temp);
  Serial.print("  Water ");
  Serial.print(Water);
  Serial.println(".");
  delay(1000); // Wait for 1000 millisecond(s)
}
