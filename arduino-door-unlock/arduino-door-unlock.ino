#include <Wire.h>
#include <Serial.h>

#define DOOR_UNLOCK_PIN 1

void setup () {
	pinMode(DOOR_UNLOCK_PIN, OUTPUT);

	Serial.begin(9600);

	//join i2c bus with ardress 8
	Wire.begin(8);
	Wire.onReceive(receiveHandler);
}

void loop() {

}

void receiveHandler() {
	int event = Wire.read();    // receive byte as an integer
	Serial.println(event);
}

