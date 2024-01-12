void updateMenu() {
  switch (menu) {
    case 0:
      menu = 1;   // Menu Boundaries
      break;
    case 1:
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.setCursor(0, 0);
      display.println("SELECT MENU");
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 20);
      display.println("-> Menu1_Team A");     // Full Mission Side A
      display.println("   Menu2_Moving");     // Moving
      display.println("   Menu3_Arm");        // Arm Mechanism
      display.println("   Menu4_Team B");     // Full Mission Side B
      display.println("   Menu5_Battery");    // Battery Capacity
      display.display();
      break;  
    case 2:
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.setCursor(0, 0);
      display.println("SELECT MENU");
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 20);
      display.println("   Menu1_Team A");     // Full Mission Side A
      display.println("-> Menu2_Moving");     // Moving
      display.println("   Menu3_Arm");        // Arm Mechanism
      display.println("   Menu4_Team B");     // Full Mission Side B
      display.println("   Menu5_Battery");    // Battery Capacity
      display.display();
      break;
    case 3:
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.setCursor(0, 0);
      display.println("SELECT MENU");
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 20);
      display.println("   Menu1_Team A");     // Full Mission Side A
      display.println("   Menu2_Moving");     // Moving
      display.println("-> Menu3_Arm");        // Arm Mechanism
      display.println("   Menu4_Team B");     // Full Mission Side B
      display.println("   Menu5_Battery");    // Battery Capacity
      display.display();
      break;
    case 4:
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.setCursor(0, 0);
      display.println("SELECT MENU");
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 20);
      display.println("   Menu1_Team A");     // Full Mission Side A
      display.println("   Menu2_Moving");     // Moving
      display.println("   Menu3_Arm");        // Arm Mechanism
      display.println("-> Menu4_Team B");     // Full Mission Side B
      display.println("   Menu5_Battery");    // Battery Capacity
      display.display();
      break;
    case 5:
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.setCursor(0, 0);
      display.println("SELECT MENU");
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 20);
      display.println("   Menu1_Team A");     // Full Mission Side A
      display.println("   Menu2_Moving");     // Moving
      display.println("   Menu3_Arm");        // Arm Mechanism
      display.println("   Menu4_Team B");     // Full Mission Side B
      display.println("-> Menu5_Battery");    // Battery Capacity
      display.display();
      break;
    case 6:
      menu = 5;   // Menu Boundaries
      break;
  }
}