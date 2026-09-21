#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 6);

int pirPin = 2;
int ldrPin = A0;
int ledPin = 8;

unsigned long lastMotionTime = 0;
const unsigned long holdTime = 10000;   // 10 seconds

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Smart Room");
  delay(2000);
  lcd.clear();
}

void loop() {

  int motion = digitalRead(pirPin);
  int light = analogRead(ldrPin);

  // Motion detected
  if (motion == HIGH) {
    lastMotionTime = millis();
  }

  // Keep person detected for 10 seconds
  bool personPresent = (millis() - lastMotionTime) < holdTime;

  lcd.clear();

  if (personPresent) {

    lcd.setCursor(0, 0);
    lcd.print("Person Found");

    // Dark room -> Light ON
    if (light < 500) {
      digitalWrite(ledPin, HIGH);

      lcd.setCursor(0, 1);
      lcd.print("Light ON");
    }
    else {
      digitalWrite(ledPin, LOW);

      lcd.setCursor(0, 1);
      lcd.print("Room Bright");
    }

  } else {

    digitalWrite(ledPin, LOW);

    lcd.setCursor(0, 0);
    lcd.print("Room Empty");

    lcd.setCursor(0, 1);
    lcd.print("Light OFF");
  }

  delay(300);
}