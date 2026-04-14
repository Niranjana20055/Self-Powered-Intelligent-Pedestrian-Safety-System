#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// I2C address 0x27 is standard for JHD 162A
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo gateServo;

// Pin Definitions
const int irSensor = 2;
const int soundSensor = 4;
const int trigPin = 6;
const int echoPin = 7;
const int buzzer = 8;
const int servoPin = 9;

// Timer for Siren
unsigned long sirenStartTime = 0; 
const long sirenHoldTime = 5000; 

void setup() {
  pinMode(irSensor, INPUT);
  pinMode(soundSensor, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  
  gateServo.attach(servoPin);
  lcd.init();
  lcd.backlight();
  
  gateServo.write(0); // Start Open
}

void loop() {
  // 1. Get Ultrasonic Distance
  long duration;
  int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // 2. Read Sensors
  int personDetected = digitalRead(irSensor);
  int sirenDetected = digitalRead(soundSensor);

  // Update siren timer if sound is heard
  if (sirenDetected == HIGH) {
    sirenStartTime = millis(); 
  }

  lcd.clear();

  // 3. LOGIC HIERARCHY
  
  // PRIORITY 1: AMBULANCE (Master Override)
  if (millis() - sirenStartTime < sirenHoldTime) {
    gateServo.write(0); // OPEN for ambulance
    lcd.setCursor(0, 0);
    lcd.print("AMBULANCE ON THE");
    lcd.setCursor(0, 1);
    lcd.print("WAY! MAKE WAY");
  } 
  // PRIORITY 2: PEDESTRIAN DETECTION (Person is present)
  else if (personDetected == LOW) { 
    gateServo.write(90); // CLOSE for cars
    lcd.setCursor(0, 0);
    lcd.print("STOP! PEDESTRIAN");
    lcd.setCursor(0, 1);
    lcd.print("CROSSING");
  } 
  // PRIORITY 3: VEHICLE PROXIMITY ALERT
  else if (distance > 0 && distance < 10) {
    gateServo.write(0); 
    lcd.setCursor(0, 0);
    lcd.print("YOU ARE TOO");
    lcd.setCursor(0, 1);
    lcd.print("CLOSE TO BARRIER");
  }
  // DEFAULT: ROAD CLEAR
  else {
    gateServo.write(0); // OPEN for cars
    lcd.setCursor(0, 0);
    lcd.print("ROAD IS CLEAR");
  }

  // 4. BUZZER CONTROL (Independent safety beep)
  if (distance > 0 && distance < 10) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }

  delay(200); 
}
