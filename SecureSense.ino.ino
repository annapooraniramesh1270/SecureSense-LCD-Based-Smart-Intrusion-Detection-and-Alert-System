// SecureSense: LCD-Based Smart Intrusion Detection and Alert System

// Include LCD library
#include <LiquidCrystal.h>

// LCD pin connections: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 6);

// Define component pins
const int pirPin = 2;      // PIR sensor output pin
const int ledPin = 8;      // LED pin
const int buzzerPin = 9;   // Buzzer pin

// Variable to store motion detection count
int motionCount = 0;

void setup() {

  // Set PIR sensor as INPUT
  pinMode(pirPin, INPUT);

  // Set LED and buzzer as OUTPUT
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initialize LCD (16 columns, 2 rows)
  lcd.begin(16, 2);

  // Display startup message
  lcd.setCursor(0, 0);
  lcd.print("SecureSense");

  lcd.setCursor(0, 1);
  lcd.print("System Armed");

  // Wait 2 seconds
  delay(2000);

  // Clear LCD
  lcd.clear();
}

void loop() {

  // Read PIR sensor value
  int motion = digitalRead(pirPin);

  // Check if motion is detected
  if (motion == HIGH) {

    // Increase motion count
    motionCount++;

    // Turn ON LED
    digitalWrite(ledPin, HIGH);

    // Activate buzzer at 1000Hz
    tone(buzzerPin, 1000);

    // Clear LCD before displaying alert
    lcd.clear();

    // First row message
    lcd.setCursor(0, 0);
    lcd.print("Motion Found!");

    // Second row message
    lcd.setCursor(0, 1);
    lcd.print("Count:");
    lcd.print(motionCount);

    // Keep alarm active for 1 second
    delay(1000);

    // Stop buzzer
    noTone(buzzerPin);
  }

  else {

    // Turn OFF LED
    digitalWrite(ledPin, LOW);

    // Ensure buzzer is OFF
    noTone(buzzerPin);

    // Clear LCD
    lcd.clear();

    // Display secure status
    lcd.setCursor(0, 0);
    lcd.print("Area Secure");

    // Show total motion count
    lcd.setCursor(0, 1);
    lcd.print("Count:");
    lcd.print(motionCount);

    // Refresh every 0.5 seconds
    delay(500);
  }
}