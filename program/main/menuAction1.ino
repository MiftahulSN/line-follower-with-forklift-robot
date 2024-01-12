void action1() {
  // Init_display
  display.setTextSize(1);  
  display.setCursor(0, 0); 
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.print("FULL MISSION");
  display.setCursor(5, 32);
  display.setTextColor(SSD1306_WHITE);
  display.print("Team_A");
  display.display();
  //Start_mission
  initStartA(); goStop(); delay(1500);
  do{
    switch(action){
      case 0:                 // position_pickup
        pos = 0;
        position("pickup");
        goStop(); delay(1000);
        action = 2;
        break;
      case 1:                 // position_dropping
        pos = 1;
        position("dropping");
        target_count++;
        goStop(); delay(1000);
        action = 3;
        break;
      case 2:                 // task_pickup
        posT = 0;
        task("pickup");
        goStop(); delay(1500);
        action = 1;
        break;
      case 3:                 // task_dropping
        posT = 0;
        task("dropping");
        goStop(); delay(1500);
        action = 0;
        break;
      default:
        // goStop();
        oledDisplay("Default");             
        break;
    }
  }while(digitalRead(resetButton) == 0 || target_count <= 5);
  goStop();
  action = 0;
  target_count = 0;
}

void position(String pos_mode){
  // Determine_sensor_based_on_mode [ternary_operator]
  sideSensor();
  bool* sensor_mode = (pos_mode == "pickup") ? &left_sensor : &right_sensor ;
  String side_mode = (pos_mode == "pickup") ? "right" : "left" ;
  do{
    if(pos == 0){
      oledDisplay("Posisi 0");
      do{
        moving();
        sideSensor();
      }while(*sensor_mode == 0);
      pos++;
      int turn1 = (pos_mode == "pickup") ? 0 : 1 ;
      posTransition(turn1, pos_mode);
      count = 0;
    }else if(pos == 1){
      if(pos_mode == "pickup"){
        if      (right_sensor == 1) count = 0;
        else if (right_sensor == 0) count = 1;
      }else{
        if      (left_sensor == 1) count = 0;
        else if (left_sensor == 0) count = 1;
      }
      do{
        if (count <= 3) counting(side_mode);
        else if (count > 3) {
          side_mode = (pos_mode == "pickup") ? "left" : "right" ;
          counting(side_mode);
        }
        oledDisplay(String(count));
        sideSensor();
        counting(side_mode);
        moving();
      }while(count <= 4);
      pos++;
      count = 0;
    }else if(pos == 2){
      oledDisplay("Posisi 2");
      count = 0;
      do{
        posTransition(3, pos_mode);
        data[2] = digitalRead(IR3);
        countingMid();  
      }while(count <= target_count);
      pos++;     
    }else{
      Serial.println("BUG Position");
    }
  }while(pos <= 2);  // loop boundaries
}

void task(String task_mode){
  // Determine_task_based_on_task_mode
  bool isPickup   = (task_mode == "pickup") ? true : false ;
  void (*go)()    = (task_mode == "pickup") ? &goPickup : &goDropping ;
  void (*back)()  = (task_mode == "pickup") ? &backPickup : &backDropping ;
  do{
    if(posT == 0){
      oledDisplay("Task 0");
      go();
      posT++;
    }else if(posT == 1){
      oledDisplay("Task 1");
      if(isPickup == true)  forkUp();
      if(isPickup == false) forkDown();
      posT++;
    }else if(posT == 2){
      oledDisplay("Task 2");
      sideSensor();
      back();
      posT++;
    }else{
      Serial.println("BUG Task");
    }
  }while(posT <= 2);
}

void posTransition(int turn, String turn_mode){
  // Determine_turn_based_on_mode
  void (*dir)(int) = (turn_mode == "pickup") ? &moveLeft : &moveRight ;
  if(turn == 0){                     // Right Sensor Rotation Benchmark
    sideSensor();
    oledDisplay("turn 0");
    while(right_sensor == 0){
      sideSensor();
      turnLeft(90);
    }
  }else if(turn == 1){               // Left Sensor Rotation Benchmark
    sideSensor();
    oledDisplay("turn 1");
    while(left_sensor == 0){
      sideSensor();
      turnRight(90);
    }
  }else if(turn == 2){               // Middle Front Sensor Rotation Benchmark  
    oledDisplay("turn 2");
    do{
      dir(90);
      data[2] = digitalRead(IR3);
    }while(data[2] == 0);
  }else if(turn == 3){
    oledDisplay("turn 3");
    do{
      dir(110);
      data[2] = digitalRead(IR3);
    }while(data[2] == 0);
  }else{
    Serial.println("BUG Transition");
  }
  // goStop(); delay(1500);
}

void counting(String side){
  // Determine_sensor_based_on_side
  bool* sensor_count = (side == "left") ? &left_sensor : &right_sensor ;
  if(*sensor_count == 1){
    if(!incremented){
      count++;
      incremented = true;
    }
  }else{
    incremented = false;
  }
}

void countingMid(){
  if(data[2] == 1){
    if(!incremented){
      count++;
      incremented = true;
    }
  }else{
    incremented = false;
  }
}

void goPickup(){
  do{
    moving();
    range = sensor.readRangeSingleMillimeters();
  }while(range > 130);
}

void goDropping(){
  unsigned long startTime = millis();
  do{
    moving();
  }while (millis() - startTime < 750);
}

void backPickup(){
  goBackward();
  delay(550);
  oledDisplay("Back A"); 
  do{                               // 50% turn
    turnLeft(90);
    sideSensor();
  }while(right_sensor == 0);
  oledDisplay("Back B");     
  do{                               // 100% turn
    turnLeft(90);
    data[2] = digitalRead(IR3);
  }while(data[2] == 0);
  oledDisplay("Back C");
  sideSensor();  
  while((left_sensor == 0)){        // moving forward
    moving();
    // goForward();
    sideSensor();
  }
  oledDisplay("Back D");
  do{
    turnLeftKhusus(90);
    sideSensor();
  }while(right_sensor == 0);
  goStop(); delay(1000);
  oledDisplay("Back E");  
  data[2] = digitalRead(IR3);
  while(data[2] == 0){              // move left
    moveLeft(80);
    data[2] = digitalRead(IR3);
  }
}

void backDropping(){
  goBackward();
  delay(550);
  oledDisplay("Back A");
  do{                               // 50% turn
    turnLeft(90);
    sideSensor();
  }while((left_sensor == 0) || (right_sensor == 0)); 
  oledDisplay("Back B");     
  do{                               // 100% turn
    turnLeft(90);
    data[2] = digitalRead(IR3);
  }while(data[2] == 0);
  oledDisplay("Back C");
  do{                               // moving forward
    moving();
    // goForward();
    sideSensor();
  }while(right_sensor == 0);
  oledDisplay("Back D"); 
  do{                               // move right
    moveRight(90);
    data[2] = digitalRead(IR3);
  }while(data[2] == 0);  
}

void initStartA(){
  do{
    goForward();
    delay(500);
    sideSensor();
  }while(right_sensor == 0);
  do{
    turnRight(90);
    data[3] = digitalRead(IR3);
  }while(data[3] == 0);
}

void oledDisplay(String text){
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(1,1);
  display.print(text);
  display.display(); 
}