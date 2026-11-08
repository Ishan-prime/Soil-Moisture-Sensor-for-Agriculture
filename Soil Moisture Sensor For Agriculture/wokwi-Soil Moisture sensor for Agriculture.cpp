#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int sensorPin = A0;  // Potentiometer / Soil sensor pin
const int ledPin = 8;      // Dry soil warning LED

// Initialize LCD (I2C address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(ledPin, OUTPUT);
  
  // Initialize LCD and turn on backlight
  lcd.init();
  lcd.backlight();

  // Initial welcome message
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture");
  lcd.setCursor(0, 1);
  lcd.print("Monitor System");
  delay(2000);
  lcd.clear();
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  
  // Map raw analog reading (1023 to 200) to moisture percentage (0% to 100%)
  int moisturePercent = map(sensorValue, 1023, 200, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  // Display values on LCD line 1
  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(moisturePercent);
  lcd.print("%   "); // Extra spaces clear leftover digits

  // Display status on LCD line 2
  lcd.setCursor(0, 1);
  if (moisturePercent < 30) {
    digitalWrite(ledPin, HIGH);
    lcd.print("Status: DRY!    ");
  } else {
    digitalWrite(ledPin, LOW);
    lcd.print("Status: WET OK  ");
  }

  delay(500);
}