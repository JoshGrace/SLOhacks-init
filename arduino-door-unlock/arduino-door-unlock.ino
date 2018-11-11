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
bool shouldFire = false;

void setup () {
	Serial.begin(19200);

	pinMode(13, OUTPUT);

	pinMode(LOCK_UNLOCK_PIN, OUTPUT);
	lockServo.attach(LOCK_UNLOCK_PIN);

	pinMode(PUSHER_PIN, OUTPUT);
	pinMode(FLYWHEELS_PIN, OUTPUT);

	digitalWrite(PUSHER_PIN, LOW);
	digitalWrite(FLYWHEELS_PIN, LOW);
}

void loop() {
	readSerial();
}

void readSerial() {
	//read Serial for commands
	if(Serial.available() > 0) {
		//convert ascii val of Serial.read() to char
       handleSerialReading(Serial.read());
    }
}


//3 is 254

//serialReading in ASCII
void handleSerialReading(int serialReading) {
	Serial.println((String)serialReading);

	lockServo.write(UNLOCKED_SERVO_ANGLE);
	delay(10000);
	lockServo.write(LOCKED_SERVO_ANGLE);



	// if (serialReading > 253) {
	// 	digitalWrite(13, HIGH);
	// }

	// //in = 0 means lock
	// //in - 1 means unlock
	// if (serialReading <= 1) {
	// 	moveLock(serialReading);
	// 	return;
	// }
		
	// //fire if anything from serial isn't 1 or 0 and if char changed
	// //and delay
	// fire();

	// if (shouldFire) {
	// 	fire(); 
	// 	shouldFire = false;
	// }

	// if (serialReading == 2) {
	// 	shouldFire = true;
	// }

	// if (serialReading == 3) {
	// 	shouldFire = false;
	// }
}

//function to unlock or lock door
//stepper rotates 90 deg upon lock/unlock
//toLock = direction as well
//clockwise = lock
//CCW = unlock
void moveLock(bool toLock) {
	// if (toLock != lockState) {	
		//lock	
		if (toLock) {
			Serial.println("Locking");
			lockServo.write(LOCKED_SERVO_ANGLE);
			lockState = toLock;
			delay(100);
			// Stream.flush();
			return;
		}

		//unlock
		Serial.println("Unlcoking");
		lockServo.write(UNLOCKED_SERVO_ANGLE);
		delay(3000);
		lockServo.write(LOCKED_SERVO_ANGLE);
		// Stream.flush();

		lockState = toLock;
	// }
	
}

void fire() {
	Serial.println("firig");

	//accel flywheel motors
	// digitalWrite(FLYWHEELS_PIN, HIGH);
	delay(FLYWHEEL_ACCEL_TIME);

	//power pusher motor for certain time to shoot one dart
	digitalWrite(PUSHER_PIN, HIGH);
	delay(ONE_DART_TIME);

	digitalWrite(PUSHER_PIN, LOW);
	digitalWrite(FLYWHEELS_PIN, LOW);

	delay(100);
	// Serial.flush();
}
