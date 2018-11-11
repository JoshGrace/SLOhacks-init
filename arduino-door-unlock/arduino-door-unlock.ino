#include <SoftwareSerial.h>
#include <Servo.h>

#define LOCK_UNLOCK_PIN 6

#define LOCKED_SERVO_ANGLE 0
#define UNLOCKED_SERVO_ANGLE 180

#define PUSHER_PIN 3
#define FLYWHEELS_PIN 5

#define FLYWHEEL_ACCEL_TIME 100
#define ONE_DART_TIME 100

Servo lockServo;

//0 = locked
//1 = unlocked
bool lockState = 0;

void setup () {
	Serial.begin(9600);

	pinMode(LOCK_UNLOCK_PIN, OUTPUT);
	lockServo.attach(LOCK_UNLOCK_PIN);

	pinMode(PUSHER_PIN, OUTPUT);
	pinMode(FLYWHEELS_PIN, OUTPUT);

	digitalWrite(PUSHER_PIN, LOW);
	digitalWrite(FLYWHEELS_PIN, LOW);
}

void loop() {
	// lockServo.write(0);
	// delay(2000);
	// lockServo.write(180);
	// delay(2000);
	readSerial();
}

void readSerial() {
	//read Serial for commands
	if(Serial.available() > 0) {
		//convert ascii val of Serial.read() to char
       handleSerialReading(Serial.read() - 48);
    }
}

//serialReading in ASCII
void handleSerialReading(int serialReading) {
	Serial.println((String)serialReading);

	//in = 0 means lock
	//in - 1 means lock
	if (serialReading <= 1) {
		moveLock(serialReading);
		return;
	}
		
	//fire if anything from serial isn't 1 or 0
	fire();
}

//function to unlock or lock door
//stepper rotates 90 deg upon lock/unlock
//toLock = direction as well
//clockwise = lock
//CCW = unlock
void moveLock(bool toLock) {
	if (toLock != lockState) {	
		//lock	git
		if (toLock) {
			Serial.println("Locking");
			lockServo.write(LOCKED_SERVO_ANGLE);
			lockState = toLock;
			delay(100);
			return;
		}

		//unlock
		Serial.println("Unlcoking");
		lockServo.write(UNLOCKED_SERVO_ANGLE);
		delay(5000);
		lockServo.write(LOCKED_SERVO_ANGLE);

		lockState = toLock;
	}
	
}

void fire() {
	Serial.println("firig");

	//accel flywheel motors
	digitalWrite(FLYWHEELS_PIN, HIGH);
	delay(FLYWHEEL_ACCEL_TIME);

	//power pusher motor for certain time to shoot one dart
	digitalWrite(PUSHER_PIN, HIGH);
	delay(ONE_DART_TIME);

	digitalWrite(PUSHER_PIN, LOW);
	digitalWrite(FLYWHEELS_PIN, LOW);	
}
