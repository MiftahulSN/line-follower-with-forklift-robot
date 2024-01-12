void action3() {
  // Init_display
  display.setTextSize(1);  
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.print("ARM MECHANISM");
  display.setCursor(5, 32);
  display.setTextColor(SSD1306_WHITE);
  display.print("Press_Up/Down");
  display.display();
  // Start_mission
  do{
	  if(digitalRead(upButton) == 1){
      myServo.writeMicroseconds(ccw);         // UP
      delay(1200);                            // Tuning Needed, depends on your manipulator
      myServo.writeMicroseconds(stop);        // Limit
      break;
    }else if(digitalRead(downButton) == 1){
      myServo.writeMicroseconds(cw);          // DOWN
      delay(1150);                            // Tuning Needed, depends on your manipulator
      myServo.writeMicroseconds(stop);        // Limit
      break;
    }
  }while(digitalRead(resetButton) == 0);
}

void forkUp(){
  myServo.writeMicroseconds(ccw);
  delay(1000);                                // Tuning Needed, depends on your manipulator
  myServo.writeMicroseconds(stop);
}

void forkDown(){
  myServo.writeMicroseconds(cw);
  delay(999);                                 // Tuning Needed, depends on your manipulator
  myServo.writeMicroseconds(stop);
}