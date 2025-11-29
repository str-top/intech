#include <DHT.h>

#define DHTPIN 2          // DHT11 data pin
#define DHTTYPE DHT11

#define buzzer 0
#define ledGreen 1
#define ledRed 2

DHT dht(DHTPIN, DHTTYPE);

// Trigger temperature
#define TEMP_LIMIT 35

void setup() {
  dht.begin();

  pinMode(buzzer, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
}

void loop() {
  float t = dht.readTemperature();

  // If reading failed skip this loop
  if (isnan(t)) {
    return;
  }

  if (t > TEMP_LIMIT) {
    tone(buzzer, 1000, 500);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
  } else {
    noTone(buzzer);
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
  }

  delay(500);
}
