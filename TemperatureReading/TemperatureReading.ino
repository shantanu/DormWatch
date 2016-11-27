#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int sensorPin = A0;
const float baselineTemp = 20.0;

/*Variables for Time Graphing*/
unsigned long previousTemp = 0;

long interval = 5000; //5 Seconds

/*Variables for Averaging Temp in a Given Time */
unsigned long currentSum = 0;
unsigned long numTemps = 0;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.print("Temperature Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Readings!");
  
}

void loop() {
  /* Code to Analyze Sensor Readings*/
      int sensorVal = analogRead(sensorPin);
      Serial.print("Sensor Value: ");
      Serial.print(sensorVal);
    
      //convert the ADC reading to voltage
      float voltage = (sensorVal/1024.0) * 5.0;
    
      Serial.print(", Volts: ");
      Serial.print(voltage);
    
      //convert the voltage to temperature in degrees
      Serial.print(", degrees C: ");
      float celcius = (voltage - .5) * 100;
      Serial.print(celcius);
    
      float fahrenheit = celcius * 1.8 + 32;
      Serial.print(", degrees F: ");
      Serial.println(fahrenheit);
    
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.setCursor(6, 0);
      lcd.print(fahrenheit);

  /* Code to Graph the Temp over a period of time */
  

  
  
}





/* QUEUE IMPLEMENTATION IN C TAKEN FROM 
 *  
 */
#include <stdlib.h>
#include <stdbool.h>

#define MAX 16

int intArray[MAX];
int front = 0;
int rear = -1;
int itemCount = 0;

int peek() {
   return intArray[front];
}

bool isEmpty() {
   return itemCount == 0;
}

bool isFull() {
   return itemCount == MAX;
}

int size() {
   return itemCount;
}  

void insert(int data) {

   if(!isFull()) {
 
      if(rear == MAX-1) {
         rear = -1;            
      }       

      intArray[++rear] = data;
      itemCount++;
   }
}
