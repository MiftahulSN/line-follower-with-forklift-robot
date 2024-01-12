#include <Servo.h>

#define cw 2000   // UP
#define ccw 1000  // DOWN
#define stop 1500 // Literally STOP
#define servo 44  // CHECK PINOUT

Servo myServo;

void setup() {
  myServo.attach(servo);   
}

void loop() {
  myServo.writeMicroseconds(ccw);         // UP
  delay(700);                             
  myServo.writeMicroseconds(stop);        // STOP
  delay(2500);
  myServo.writeMicroseconds(cw);          // DOWN
  delay(600);                             
  myServo.writeMicroseconds(stop);        // STOP
}       