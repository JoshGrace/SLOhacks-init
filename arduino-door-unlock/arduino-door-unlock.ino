#include <Wire.h>
#include <SoftwareSerial.h>
#include <CheapStepper.h>

#define DOOR_UNLOCK_PIN 1

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

CheapStepper doorStepper (IN1, IN2, IN3, IN4);

bool isClockwise = true;


void setup () {
	pinMode(DOOR_UNLOCK_PIN, OUTPUT);

	Serial.begin(9600);

	//join i2c bus with ardress 8
	Wire.begin(8);
	Wire.onReceive(receiveHandler);

}

void loop() {
	
}

//event is int received from RPI
//0 = lock door
//1 = unlock door
void receiveHandler(int a) {
	int event = Wire.read();    // receive byte as an integer
	Serial.println(event);
}

void unlockDoor() {

}

