#include <Wire.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#define DOOR_UNLOCK_PIN 1
#define DOOR_SERVO_PIN 3

Servo doorServo;

int servoAngle = 0;

void setup () {
	pinMode(DOOR_UNLOCK_PIN, OUTPUT);

	Serial.begin(9600);

	//join i2c bus with ardress 8
	Wire.begin(8);
	Wire.onReceive(receiveHandler);

	//Servo setup
	doorServo.attach(DOOR_SERVO_PIN);
}

void loop() {
	doorServo.write(45);
	delay(1000);
	doorServo.write(90);
	delay(1000);
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

