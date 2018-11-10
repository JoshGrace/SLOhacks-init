#include <Wire.h>
#include <SoftwareSerial.h>
#include <CheapStepper.h>

#define DOOR_UNLOCK_PIN 1

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

#define PUSHER_PIN 3
#define FLYWHEELS_PIN 5

#define FLYWHEEL_ACCEL_TIME 100
#define ONE_DART_TIME 100

CheapStepper doorStepper (IN1, IN2, IN3, IN4);

void setup () {
	pinMode(DOOR_UNLOCK_PIN, OUTPUT);

	Serial.begin(9600);

	//join i2c bus with ardress 8
	Wire.begin(8);
	Wire.onReceive(receiveHandler);

	pinMode(PUSHER_PIN, OUTPUT);
	pinMode(FLYWHEELS_PIN, OUTPUT);

	digitalWrite(PUSHER_PIN, LOW);
	digitalWrite(FLYWHEELS_PIN, LOW);
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

//function to unlock or lock door
//stepper rotates 90 deg upon lock/unlock
//toLock = direction as well
//clockwise = lock
//CCW = unlock
void moveLock(bool toLock) {
	for (int i = 0; i < 1024; i++) {
		doorStepper.step(toLock);
		Serial.println((String)doorStepper.getStepsLeft());
	}
}

void fireOneDart() {
	digitalWrite(FLYWHEELS_PIN, HIGH);
	delay(FLYWHEEL_ACCEL_TIME);
	digitalWrite(PUSHER_PIN, HIGH);
	delay(ONE_DART_TIME);

	digitalWrite(PUSHER_PIN, LOW);
	digitalWrite(FLYWHEELS_PIN, LOW);	
}