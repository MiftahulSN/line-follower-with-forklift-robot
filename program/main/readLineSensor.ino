// [Front_Sensor] Left --> Right (Upper View) 
void lineSensor(){
  data[0] = digitalRead(IR1);
  // Serial.print("Sensor 1 : ");
  // Serial.println(data[0]);
  delay(1);

  data[1] = digitalRead(IR2);
  // Serial.print("Sensor 2 : ");
  // Serial.println(data[1]);
  delay(1);

  data[2] = digitalRead(IR3);
  // Serial.print("Sensor 3 : ");
  // Serial.println(data[2]);
  delay(1);

  data[3] = digitalRead(IR4);
  // Serial.print("Sensor 4 : ");
  // Serial.println(data[3]);
  delay(1);

  data[4] = digitalRead(IR5);
  // Serial.print("Sensor 5 : ");
  // Serial.println(data[4]);
  delay(1);

  return data[0], data[1], data[2], data[3], data[4];
}

// [Side_Sensor]
void sideSensor(){
  left_sensor = digitalRead(IR_Left);
  // Serial.print("Sensor Samping Kiri : ");
  // Serial.println(left_sensor);
  delay(1);

  right_sensor = digitalRead(IR_Right);
  // Serial.print("Sensor Samping Kanan : ");
  // Serial.println(right_sensor);
  delay(1);

  return left_sensor, right_sensor;
}
