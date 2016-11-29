/*
 * THIS CODE LISTENS TO VALUES FROM THE SOUND SENSOR
 * AND THEN IMPLEMENTS THE FOLLOWING ALGORITHM FOR DETERMINING 
 * WHETHER THE NOISE LEVEL IS TOO HIGH:
 * 
 * THRESHOLD VALUE FOR THE SOUND SENSOR IS WHEN IT IS TOO LOUD AT A GIVEN INSTANT
 * COUNTER IS HOW MANY TIMES THE SOUND SENSOR VALUE EXCEEDS THE THRESHOLD IN THE GIVEN INTERVAL
 * LCDTHRESHOLD IS THE THRESHOLD VALUE FOR COUNTER BEFORE THE LED LIGHTS UP
 * 
 * THE LCD DISPLAYS THE SOUND SENSOR LEVEL AND THE COUNTER.
 */

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int sensorPin = A0;
const int lightPin = 8;
const int piezoPin = 8;

const int threshold = 25;
long counter = 0;
const int lcdThreshold = 80;

unsigned long previousTime = 0;
unsigned long currentTime = 0;
long interval = 25000; //10 secs


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(8, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();
  
  int sensorVal = analogRead(A0);
  Serial.println(sensorVal);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Noise: ");
      lcd.setCursor(8, 0);
      lcd.print(sensorVal);
      lcd.setCursor(0, 1);
      lcd.print("High: ");
      lcd.setCursor(8, 1);
      lcd.print(counter);

  if (currentTime - previousTime < interval){
    if (sensorVal > threshold) {
      counter++;
    }
    if (counter > lcdThreshold){
      digitalWrite(8, HIGH);
      lcd.setCursor(12, 0);
      //lcd.clear();
      lcd.print("Shhhh");
      tone(7, 440, 5);
    }
    else{
      digitalWrite(8, LOW);
    }
  }
  else {
    previousTime = currentTime;
    counter = 0;
    
  }
  delay(10); 
}
