#include <SoftwareSerial.h>

void setup() {
  // put setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
     if (Serial.read() == 111) {
        digitalWrite(13, HIGH);
     } else {
      digitalWrite(13, LOW);
     }
  }
}
