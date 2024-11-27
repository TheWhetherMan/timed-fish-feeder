/**
*  Automatic Fish Feeder
*  12/19/14
**/

#include <Servo.h>
#include <Time.h>
#include <TimeAlarms.h>

Servo servo;
int LEDPin = 5;
int motorPin = 9;
int days = 0;
unsigned long time = 0;

void setup() {
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  
  time = millis();
}

void loop() {
  Serial.println(time);
  delay(1000);
  
  // 86,400,000 = 1 day
  // Note: MUST POWER UP AT DESIRED TIME
  if (time >= 86400000 && days <= 4) {
    dispenseFood(); 
    days++;
    time = 0;
  }
  
  time = millis();
}

// Call LED flash and motor methods
void dispenseFood() {
  for (int i = 0; i < 5; i++) {
    flashLED();
  }
  spinMotor();
}

// Vibrate the dispensor tray
void spinMotor() {
  digitalWrite(motorPin, HIGH);
  delay(100);
  digitalWrite(motorPin, LOW);
}

// Pulse alert LED
void flashLED() {
  // Use PWM for LED on
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) {
    analogWrite(LEDPin, fadeValue);
    delay(5);                            
  } 
  
  delay(500);

  // Use PWM for LED off
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) {
    analogWrite(LEDPin, fadeValue); 
    delay(30);                            
  }
}

// Print clock to serial port
void digitalClockDisplay()
{
  // Digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
