const uint8_t ledG = 3;
const uint8_t ledB = 5;
const uint8_t ledR = 6;
#define trigPin 10
#define echoPin 9
#define Buzzer 8

void setup()
{
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  long durationindigit, distanceincm;
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  durationindigit = pulseIn(echoPin, HIGH);
  distanceincm = (durationindigit * 0.034) / 2;
  Serial.println(distanceincm );
  if (distanceincm >= 3 && distanceincm <=90){
    analogWrite(ledG, 0);
    analogWrite(ledB, 0);
    analogWrite(ledR, 255);
    tone(Buzzer, 3000, 250);
    delay(100);
  }
  if (distanceincm > 90 && distanceincm <=170){
    analogWrite(ledG, 255);
    analogWrite(ledB, 0);
    analogWrite(ledR, 255);
    noTone(Buzzer);
    delay(100);
  }
  if (distanceincm > 170 && distanceincm <=255){
    analogWrite(ledG, 255);
    analogWrite(ledB, 0);
    analogWrite(ledR, 0);
    noTone(Buzzer);
    delay(100);
  }
}
