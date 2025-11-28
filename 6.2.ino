void setup()
{

	Serial.begin(
		9600); // Set the serial monitor baudrate to 9600

	pinMode(13, OUTPUT); // Output LED Level 1
	pinMode(12, OUTPUT); // Output LED Level 2
	pinMode(11, OUTPUT); // Output LED Level 3
	pinMode(10, OUTPUT); // Output LED Level 4
	pinMode(9, OUTPUT); // Output LED Level 5
}

void loop()
{
	// Variable to store ADC value ( 0 to 1023 )
	int level;
	// analogRead function returns the integer 10 bit integer (0 to 1023)
	level = analogRead(0);
	// Print text in serial monitor
	Serial.println("Analog value:");
	// Print output voltage in serial monitor
	Serial.println(level);

	// Turn off All LEDs
	digitalWrite(13, LOW);
	digitalWrite(12, LOW);
	digitalWrite(11, LOW);
	digitalWrite(10, LOW);
	digitalWrite(9, LOW);

	// output of sensor varies from 0 to 4.28 Volts,
	// It's equivalent ADC value is 0 to 877 ( (4.28/5)*1024 = 877 )

	// Splitting 877 into 5 level => 175, 350, 525, 700, 877
	// Based on the ADC output, LED indicates the level (1 to 5).

	if (level < 175) {
		// LEVEL 1 LED
		digitalWrite(13, HIGH);
	}
	else if (level < 350) {
		// LEVEL 2 LED
		digitalWrite(12, HIGH);
	}
	else if (level < 525) {
		// LEVEL 3 LED
		digitalWrite(11, HIGH);
	}
	else if (level < 700) {
	// LEVEL 4 LED
		digitalWrite(10, HIGH);
	}
	else if (level < 876) {
		// LEVEL 5 LED
		digitalWrite(9, HIGH);
	}
}
