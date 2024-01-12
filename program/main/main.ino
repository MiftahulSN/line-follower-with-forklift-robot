// Library
#include <Wire.h>
#include <Servo.h>
#include <VL53L0X.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// motor_1_left_back
#define enA 2 //pwm
#define in1 3 //direction
#define in2 4 //direction
// motor_2_left_front
#define enB 5 //pwm
#define in3 6 //direction
#define in4 7 //direction
// motor_3_right_front
#define enC 8  //pwm
#define in5 9  //direction
#define in6 10 //direction
// motor_4_right_back
#define enD 13 //pwm
#define in7 11 //direction
#define in8 12 //direction
// battery
#define battery A8
// oled
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C
// servo
#define cw 2000   // UP
#define ccw 1000  // DOWN
#define stop 1500 // Literally STOP
// Calling_oled_method
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 0x3C);  // Hapus -1 (reset) jika error
// Calling_lidar_method
VL53L0X sensor;
// Calling_servo_method
Servo myServo;

// Pinout_sensor_and_aktuator
const int servo         = 44; // Cek pinout
const int upButton      = 34; // Cek pinout
const int downButton    = 32; // Cek pinout
const int resetButton   = 30; // Cek pinout
const int selectButton  = 28; // Cek pinout
const int IR1 = 50;           // Cek pinout
const int IR2 = 51;           // Cek pinout
const int IR3 = 49;           // Cek pinout
const int IR4 = 52;           // Cek pinout
const int IR5 = 53;           // Cek pinout
const int IR_Left   = 48;     // Cek pinout
const int IR_Right  = 46;     // Cek pinout

#define analogIR1       A3
#define analogIR2       A2
#define analogIR3       A5
#define analogIR4       A1
#define analogIR5       A0
#define analogIR_Left   A6
#define analogIR_Right  A7

// Initialize_mission_variable
int range = 0;
int error = 0;
int menu = 1;
int pos = 0;
int posT = 0;
int count = 0;
int action = 0;
int lastError = 0;
int target_count = 0;
bool left_sensor;
bool right_sensor;
bool incremented = false;
bool data[5];

void setup() {
  Serial.begin(9600);
  myServo.attach(servo);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("OLED FAILED"));
    for(;;);
  }
  // display.display(); delay(1500);
  display.clearDisplay();
  // Setup_button
  pinMode(battery, INPUT);
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
  pinMode(resetButton, INPUT);
  pinMode(selectButton, INPUT);
  // Setup_line_sensor
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  pinMode(IR_Left, INPUT);
  pinMode(IR_Right, INPUT);
  // Setup_motor 
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
  // Lidar_init
  initLidar();
  // Robot_init
  entranceOled(); delay(1500);
  updateMenu();
  goStop();
}

void loop() {
  if (digitalRead(downButton) == 1){
    menu++;
    updateMenu();
    delay(50);
    while (digitalRead(downButton) == 1);
  }
  if (digitalRead(upButton)){
    menu--;
    updateMenu();
    delay(50);
    while(digitalRead(upButton) == 1);
  }
  if (digitalRead(selectButton)){
    executeAction();
    updateMenu();
    delay(50);
    while (digitalRead(selectButton));
  }
}

void executeAction() {
  display.clearDisplay();
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;
    case 5:
      batteryCheck();
      break;
  }
}

void entranceOled(){
  display.drawPixel(0, 0, SSD1306_WHITE);
  display.drawPixel(126, 0, SSD1306_WHITE);
  display.drawPixel(0, 62, SSD1306_WHITE);
  display.drawPixel(126, 62, SSD1306_WHITE);

  display.setTextSize(2);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.setCursor(10, 13);
  display.print(F("ROBOTICS"));

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(42, 43);
  display.print(F("Team 5"));

  display.display();
}

void initLidar(){
  Wire.begin();
  sensor.setTimeout(500);
  if (!sensor.init()){
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.setMeasurementTimingBudget(200000);
}