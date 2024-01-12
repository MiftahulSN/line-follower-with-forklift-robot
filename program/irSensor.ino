int sensor_depan_1 = 22;        // Cek PINOUT
int sensor_depan_2 = 24;        // Cek PINOUT
int sensor_depan_3 = 26;        // Cek PINOUT
int sensor_depan_4 = 28;        // Cek PINOUT
int sensor_depan_5 = 30;        // Cek PINOUT
int sensor_samping_kiri  = 1;   // Cek PINOUT
int sensor_samping_kanan = 2;   // Cek PINOUT

void setup() {
  pinMode(sensor_depan_1, INPUT);
  pinMode(sensor_depan_2, INPUT);
  pinMode(sensor_depan_3, INPUT);
  pinMode(sensor_depan_4, INPUT);
  pinMode(sensor_depan_5, INPUT);
  pinMode(sensor_samping_kiri, INPUT);
  pinMode(sensor_samping_kanan, INPUT);

  Serial.begin(9600);
}

void loop() {
  bool data1 = digitalRead(sensor_depan_1);
  Serial.print("Sensor_Depan 1 : ");
  Serial.println(data1);
  delay(1);
  
  bool data2 = digitalRead(sensor_depan_2);
  Serial.print("Sensor_Depan 2 : ");
  Serial.println(data2);
  delay(1);

  bool data3 = digitalRead(sensor_depan_3);
  Serial.print("Sensor_Depan 3 : ");
  Serial.println(data3);
  delay(1);

  bool data4 = digitalRead(sensor_depan_4);
  Serial.print("Sensor_Depan 4 : ");
  Serial.println(data4);
  delay(1);

  bool data5 = digitalRead(sensor_depan_5);
  Serial.print("Sensor_Depan 5 : ");
  Serial.println(data5);
  delay(1);

  bool left_sensor = digitalRead(sensor_samping_kiri);
  Serial.print("\nSensor Samping Kiri\t: ");
  Serial.println(left_sensor);
  delay(1);

  bool right_sensor = digitalRead(sensor_samping_kanan);
  Serial.print("Sensor Samping Kanan\t: ");
  Serial.println(right_sensor);
  delay(1);

  Serial.println("\n");
  delay(1000);
}
