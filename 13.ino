int lamp=3;
int pot=A1;
int Vpot;

void setup()
{
  pinMode(lamp, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  Vpot=analogRead(pot);
  Serial.println(Vpot);
  int yarkost=map(Vpot,54,974,255,0);
  analogWrite(lamp,yarkost);
}
