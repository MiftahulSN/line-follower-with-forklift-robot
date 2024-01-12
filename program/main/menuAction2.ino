void action2() {
  // Init_display
  display.clearDisplay();
  display.setTextSize(1);  
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.print("MOVING");
  display.setCursor(5, 32);
  display.setTextColor(SSD1306_WHITE);
  display.print("Line_Follow");
  display.display();
  // Start_mission
  do{
    moving();
  }while(digitalRead(resetButton) == 0);
  goStop();
}

void moving(){
  calcError();
  if(error == 2){
    calcError();
    turnLeft(90);
  }else if(error == 1){
    calcError();
    turnLeft(80);
  }else if(error == 0){
    calcError();
    goForward();
  }else if(error == -1){
    calcError();
    turnRight(80);
  }else if(error == -2){
    calcError();
    turnRight(90);
  }
}

int calcError(){
  lineSensor();
  if((data[0] == 1) && (data[1] == 0) && (data[2] == 0) && (data[3] == 0) && (data[4] == 0)) {
    error = 2;
    lastError = error;
    return error;
  }else if((data[0] == 0) && (data[1] == 1) && (data[2] == 0) && (data[3] == 0) && (data[4] == 0)) {
    error = 1;
    lastError = error;
    return error;
  }else if((data[0] == 0) && (data[1] == 0) && (data[2] == 1) && (data[3] == 0) && (data[4] == 0)) {
    error = 0;
    lastError = error;
    return error;
  }else if((data[0] == 0) && (data[1] == 0) && (data[2] == 0) && (data[3] == 1) && (data[4] == 0)) {
    error = -1;
    lastError = error;
    return error;
  }else if((data[0] == 0) && (data[1] == 0) && (data[2] == 0) && (data[3] == 0) && (data[4] == 1)) {
    error = -2;
    lastError = error;
    return error;
  }else if((data[0] == 0) && (data[1] == 0) && (data[2] == 0) && (data[3] == 0) && (data[4] == 0)) {
    error = lastError;
    return error;
  }else{
    error = 0;
    return error;
  }
}

void fixedPwm(){
  analogWrite(enA, 120);
  analogWrite(enB, 120);
  analogWrite(enC, 120);
  analogWrite(enD, 120);
}

void modifPwm(int pwm){
  analogWrite(enA, pwm);
  analogWrite(enB, pwm);
  analogWrite(enC, pwm);
  analogWrite(enD, pwm);
}

void turnPwm(int pwm){
  analogWrite(enA, pwm);
  analogWrite(enB, pwm);
  analogWrite(enC, pwm);
  analogWrite(enD, pwm);
}

void goForward(){
  fixedPwm();
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
  fixedPwm();
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	digitalWrite(in5, LOW);
	digitalWrite(in6, HIGH);
	digitalWrite(in7, LOW);
	digitalWrite(in8, HIGH);  
}

void turnLeft(int pwm){
  turnPwm(pwm);
  digitalWrite(in1, LOW);   //backward
	digitalWrite(in2, HIGH);  //backward
	digitalWrite(in3, LOW);   //backward
	digitalWrite(in4, HIGH);  //backward
	digitalWrite(in5, HIGH);  //forward
	digitalWrite(in6, LOW);   //forward
	digitalWrite(in7, HIGH);  //forward
	digitalWrite(in8, LOW);   //forward
}

void turnLeftKhusus(int pwm){
  analogWrite(enA, pwm + 50);
  analogWrite(enB, pwm + 50);
  analogWrite(enC, pwm);
  analogWrite(enD, pwm);
  digitalWrite(in1, LOW);   //backward
	digitalWrite(in2, HIGH);  //backward
	digitalWrite(in3, LOW);   //backward
	digitalWrite(in4, HIGH);  //backward
	digitalWrite(in5, HIGH);  //forward
	digitalWrite(in6, LOW);   //forward
	digitalWrite(in7, HIGH);  //forward
	digitalWrite(in8, LOW);   //forward
}

void turnRight(int pwm){
  turnPwm(pwm);
  digitalWrite(in1, HIGH);  //forward
	digitalWrite(in2, LOW);   //forward
	digitalWrite(in3, HIGH);  //forward
	digitalWrite(in4, LOW);   //forward
	digitalWrite(in5, LOW);   //backward
	digitalWrite(in6, HIGH);  //backward
	digitalWrite(in7, LOW);   //backward
	digitalWrite(in8, HIGH);  //backward
}

void moveRight(int pwm){
  turnPwm(pwm);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
}

void moveLeft(int pwm){
  turnPwm(pwm);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
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

// ENCODER NOTES
// Best Performance : Both signals connect to interrupt pins. In Arduino Mega 2,3,18,19,20,21.
// Good Performance : First signal connects to an interrupt pin, second to a non-interrupt pin.
// Low Performance  : Both signals connect to non-interrupt pins