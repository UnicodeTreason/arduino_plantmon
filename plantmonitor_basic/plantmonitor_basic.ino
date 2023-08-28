#include "PlantMonitor.h"
#include "LiquidCrystal.h"

PlantMonitor pm = PlantMonitor(6, 5);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  //Bootup Hardware
  Serial.begin(9600);
  lcd.begin(16, 2);

  //Disable inbuilt LED
  pm.ledOff();

  //End Bootup
  lcd.print("Hello, World!");
  delay(5000);
}

void loop() {
  //Allow LED toggle
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == 'l') {
      pm.ledOff();
    }
    else if (cmd == 'L') {
      pm.ledOn();
    }
  }

  //Every 10s report data to screen and serial
  delay(10000);
  report();
}

void report() {
  //Collect data from sensors
  int moist = pm.getWater();
  float humid = pm.getHumidity();
  float temp = pm.getTemp();
  
  //Print data to Serial
  Serial.print("Moisture (%): ");
  Serial.print(moist);
  Serial.print(" Humidity (%): ");
  Serial.print(humid, 0);
  Serial.print(" Temp (C): ");
  Serial.println(temp, 0);
  
  //Print data to LCD
  lcd.setCursor(0, 0);
  lcd.print("Moist (%): ");
  lcd.print(moist);
  lcd.setCursor(0, 1);
  lcd.print("Humid:");
  lcd.print(humid, 0);
  lcd.print(" Temp:");
  lcd.print(temp, 0);
}
