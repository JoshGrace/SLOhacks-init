#include <SoftwareSerial.h>
#include <CheapStepper.h>

#define DOOR_UNLOCK_PIN 2

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

#define PUSHER_PIN 3
#define FLYWHEELS_PIN 5

#define FLYWHEEL_ACCEL_TIME 100
#define ONE_DART_TIME 100

CheapStepper doorStepper (IN1, IN2, IN3, IN4);

//0 = locked
//1 = unlocked
bool lockState = 0;

void setup () {
	pinMode(DOOR_UNLOCK_PIN, OUTPUT);

	Serial.begin(9600);

	pinMode(PUSHER_PIN, OUTPUT);
	pinMode(FLYWHEELS_PIN, OUTPUT);

	digitalWrite(PUSHER_PIN, LOW);
	digitalWrite(FLYWHEELS_PIN, LOW);
}

void loop() {
	readSerial();
}

void readSerial() {
	if(Serial.available() > 0) {
       handleSerialReading(Serial.read());
    }
}

void handleSerialReading(int in) {
	if (in >= 1) {
		moveLock(in);
		return;
	}

	fire(in - 10);
}

//function to unlock or lock door
//stepper rotates 90 deg upon lock/unlock
//toLock = direction as well
//clockwise = lock
//CCW = unlock
void moveLock(bool toLock) {
	if (toLock != lockState) {
		for (int i = 0; i < 1024; i++) {
			doorStepper.step(toLock);
			Serial.println((String)doorStepper.getStepsLeft());
		}

		lockState = toLock;
	}
	
}

void fire(int numOfDarts) {
	digitalWrite(FLYWHEELS_PIN, HIGH);
	delay(FLYWHEEL_ACCEL_TIME);
	digitalWrite(PUSHER_PIN, HIGH);
	delay(ONE_DART_TIME * numOfDarts);

	digitalWrite(PUSHER_PIN, LOW);
	digitalWrite(FLYWHEELS_PIN, LOW);	
}
