/*
   THIS CODE LISTENS TO VALUES FROM THE SOUND SENSOR
   AND THEN IMPLEMENTS THE FOLLOWING ALGORITHM FOR DETERMINING
   WHETHER THE NOISE LEVEL IS TOO HIGH:

   THRESHOLD VALUE FOR THE SOUND SENSOR IS WHEN IT IS TOO LOUD AT A GIVEN INSTANT
   COUNTER IS HOW MANY TIMES THE SOUND SENSOR VALUE EXCEEDS THE THRESHOLD IN THE GIVEN INTERVAL
   LEDTHRESHOLD IS THE THRESHOLD VALUE FOR COUNTER BEFORE THE LED LIGHTS UP

   THE LCD DISPLAYS THE SOUND SENSOR LEVEL AND THE COUNTER.
*/

#include <LiquidCrystal.h>

#include <Time.h>
#include <TimeLib.h>

#include <Time.h>

#define TIME_MSG_LEN  11   // time sync to PC is HEADER and unix time_t as ten ascii digits
#define TIME_HEADER  255   // Header tag for serial time sync message
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int sensorPin = A0;
const int lightPin = 8;
const int piezoPin = 8;

const int threshold = 40;//50
long counter = 0;
const int ledThreshold = 50;//80

unsigned long previousTime = 0;

long interval = 25000; //10 secs

/* Create the bytes for the sound bar boxes */
byte eight_line[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

byte threshold_line[8] = {
  B00110,
  B00110,
  B00110,
  B00110,
  B00110,
  B00110,
  B00110,
  B00110,
};


void noiseBar(int sensorVal){
   // Place the threshold line on the 8th box on the 2nd row
   lcd.setCursor(10, 1);
   lcd.write(byte(1));
   sensorVal = max(0, min(sensorVal, 80));
   int numBoxes = sensorVal/5;
   for(int i = 0; i <= numBoxes; i++){
    lcd.setCursor(i, 1);
    lcd.write(byte(0));
   }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(8, OUTPUT);
  lcd.createChar(0, eight_line);
  lcd.createChar(1, threshold_line);
}

void loop() {
  // put your main code here, to run repeatedly:
  listen();
  
/*if(weekday()==1&&weekday()==7)//If day of the week is Sunday(1) or Saturday(7)
  {
   if(hour()>0&&hour()<10)//Quiet hours are between 12 and 10
   {
    listen();
  }
   else
   {
      listen();
    }
  }
  else
  {
  if(hour()>=23||hour()<10)//Quiet hours are after 11pm or before 10am
   {
      listen();
    }
   else
   {
      listen();
    }
  }
  
 */
}

void listen()
{
  
  int sensorVal = analogRead(A0);
  Serial.println(sensorVal);
  // Normal Operations - N means the sensor value, H means the counter of high values
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("N: ");
  lcd.setCursor(3, 0);
  lcd.print(sensorVal);
  lcd.setCursor(6, 0);
  lcd.print("H: ");
  lcd.setCursor(9, 0);
  lcd.print(counter);
  noiseBar(sensorVal);
 // Increase the counter if the sensor value exceeds the sound threshold
  if (sensorVal > threshold) {
    counter++;
  }
  
  // The LED must light up for 15 seconds if 
  // the sound level is exceeded for a given amount of time, in this case
  // when the counter exceeds 80. 
  if (counter > ledThreshold) {
    //highNoise();
    unsigned long timeStart = millis();
  
    // Print a message telling people to be quiet
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SHHHHHHHHHHH");
    lcd.setCursor(0, 1);
    lcd.print("BE QUIET!!!!"); 
    // Turn the LED on
    digitalWrite(8, HIGH);
  
    // Keep the message on the lcd screen and the led on for 15 seconds
    while (millis() - timeStart < 8000) {
      // play a tone to annoy people
      tone(7, 440, 5);
      
      // magical wait statement
      delay(5);
     }
     
     // After the current period is over, turn the LED off, and the tone will 
     // automatically stop playing.
     digitalWrite(8, LOW);
     previousTime = millis();
     counter = 0;
  }
  

  // After each 25-second period of over, set the time comparator to the current time
  // and reset the high counter.
  if (millis() - previousTime > interval) {
    previousTime = millis();  
    counter = 0;

  }
  delay(10);

}




