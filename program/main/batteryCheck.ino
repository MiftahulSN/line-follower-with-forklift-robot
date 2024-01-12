float Volt  = 0.0;       // Volt : Battery Volt Display 
float Vout  = 0.0;       // Vout : Battery Volt Divider
float Vin   = 0.0;       // Vin  : Battery Voltage
float R1    = 35000.0;   // Resistor 35k  ohm
float R2    = 51000.0;   // Resistor 49k ohm
int val     = 0;         // Value Mapping
int value   = 0;         // Value Analog Pin

void batteryCheck(){
  // Start_mission
  do{
    calculateBattery();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    display.print("BATTERY CAPASITY");

    display.setCursor(0, 25);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.print("Voltage : ");
    display.print(Volt, 1);
    display.print(" V");

    display.setCursor(0, 40);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.print("Percent : ");
    display.print(val);
    display.print(" %");
    display.display();
    delay(10);
  }while(digitalRead(resetButton) == 0);
}

void calculateBattery(){
  value = analogRead(battery);        // Reading Analog
  Vout  = (value*5.12)/1024.0;        // Vout = ((R1/(R1+R2))*Vin)
  Vin   = (Vout*(R1+R2))/R1;          // Vin  = Vout/R1*(R1+R2)
  Vin   = Vin*10;                     // Calculate Vin for Integer Mapping
  val   = map(Vin,99,126,0,100);      // Mapping Vin Value for Display
  Volt  = Vin/10;                     // Voltage Value
}