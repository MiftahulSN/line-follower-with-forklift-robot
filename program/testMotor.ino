// motor_1_left_back
#define enA 2 //pwm             // CHECK PINOUT
#define in1 3 //direction       // CHECK PINOUT
#define in2 4 //direction       // CHECK PINOUT
// motor_2_left_front
#define enB 5 //pwm             // CHECK PINOUT
#define in3 6 //direction       // CHECK PINOUT
#define in4 7 //direction       // CHECK PINOUT
// motor_3_right_front
#define enC 8 //pwm             // CHECK PINOUT
#define in5 9 //direction       // CHECK PINOUT
#define in6 10 //direction      // CHECK PINOUT
// motor_4_right_back
#define enD 13 //pwm            // CHECK PINOUT
#define in7 11 //direction      // CHECK PINOUT
#define in8 12 //direction      // CHECK PINOUT

void setup() {
  pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
  pinMode(enC, OUTPUT);
  pinMode(enD, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);
  goStop();
}

void loop() {
  fixedPwm();
  // note : select one of the functions below
  goForward();
  // goBackward();
  // turnLeft();
  // turnRight();
  // moveLeft();
  // moveRight();
}

void fixedPwm(){
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  analogWrite(enC, 255);
  analogWrite(enD, 255);
}

void goForward(){
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
	digitalWrite(in6, LOW);
	digitalWrite(in7, HIGH);
	digitalWrite(in8, LOW);  
}

void goBackward(){
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	digitalWrite(in5, LOW);
	digitalWrite(in6, HIGH);
	digitalWrite(in7, LOW);
	digitalWrite(in8, HIGH);  
}

void turnLeft(){
  digitalWrite(in1, LOW);   //backward
	digitalWrite(in2, HIGH);  //backward
	digitalWrite(in3, LOW);   //backward
	digitalWrite(in4, HIGH);  //backward
	digitalWrite(in5, HIGH);  //forward
	digitalWrite(in6, LOW);   //forward
	digitalWrite(in7, HIGH);  //forward
	digitalWrite(in8, LOW);   //forward
}

void turnRight(){
  digitalWrite(in1, HIGH);  //forward
	digitalWrite(in2, LOW);   //forward
	digitalWrite(in3, HIGH);  //forward
	digitalWrite(in4, LOW);   //forward
	digitalWrite(in5, LOW);   //backward
	digitalWrite(in6, HIGH);  //backward
	digitalWrite(in7, LOW);   //backward
	digitalWrite(in8, HIGH);  //backward
}

void moveRight(){
  digitalWrite(in1, LOW);   //backward
  digitalWrite(in2, HIGH);  //backward
  digitalWrite(in3, HIGH);  //forward
  digitalWrite(in4, LOW);   //forward
  digitalWrite(in5, LOW);   //backward
  digitalWrite(in6, HIGH);  //backward
  digitalWrite(in7, HIGH);  //forward
  digitalWrite(in8, LOW);   //forward
}

void moveLeft(){
  digitalWrite(in1, HIGH);  //forward
  digitalWrite(in2, LOW);   //forward
  digitalWrite(in3, LOW);   //backward
  digitalWrite(in4, HIGH);  //backward
  digitalWrite(in5, HIGH);  //forward
  digitalWrite(in6, LOW);   //forward
  digitalWrite(in7, LOW);   //backward
  digitalWrite(in8, HIGH);  //backward
}

void goStop(){
  digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
	digitalWrite(in5, LOW);
	digitalWrite(in6, LOW);
	digitalWrite(in7, LOW);
	digitalWrite(in8, LOW);
}
