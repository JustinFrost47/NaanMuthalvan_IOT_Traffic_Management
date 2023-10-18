#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address, rows, columns
Ultrasonic ultrasonic(13, 12); // Trig (GPIO 13), Echo (GPIO 12) pins for HC-SR04

int vehicleCount = 0;

void setup() {
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Vehicle Count:");
}

void loop() {
  // Measure distance using the ultrasonic sensor
  long distance = ultrasonic.read(CM);

  // Adjust this distance threshold as needed to classify vehicles
  if (distance < 30) {
    // Assuming a vehicle is within 30 cm of the sensor
    vehicleCount++;
    updateLCD(vehicleCount);
    delay(2000); // Adjust delay to prevent multiple counts for one vehicle
  }

  // Determine traffic conditions based on vehicle count
  if (vehicleCount < 10) {
    lcd.setCursor(0, 1);
    lcd.print("Traffic: Low   "); // Clear the previous status and print "Low"
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Traffic: High   "); // Clear the previous status and print "High"
  }
}

void updateLCD(int count) {
  lcd.setCursor(0, 1);
  lcd.print("                "); // Clear the previous count
  lcd.setCursor(0, 1);
  lcd.print(count);
}
