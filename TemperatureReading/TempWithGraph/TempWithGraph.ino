#include <Plotter.h>


#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int sensorPin = A0;
const float baselineTemp = 20.0;

double  temperature;
Plotter p;

void setup () {
  p = Plotter();
  p.AddTimeGraph("Temperature vs. Time", 500, "Temperature", temperature);
  lcd.begin(16, 2);
}




void loop() {
  /* Code to Analyze Sensor Readings*/
      int sensorVal = analogRead(sensorPin);
      //Serial.print("Sensor Value: ");
      //Serial.print(sensorVal);
    
      //convert the ADC reading to voltage
      float voltage = (sensorVal/1024.0) * 5.0;
    
      //Serial.print(", Volts: ");
      //Serial.print(voltage);
    
      //convert the voltage to temperature in degrees
      //Serial.print(", degrees C: ");
      float celcius = (voltage - .5) * 100;
      //Serial.print(celcius);
    
      float temperature = celcius * 1.8 + 32;
      //Serial.print(", degrees F: ");
      Serial.println(temperature);
    
      lcd.clear();
      lcd.setCursor(0, 0);
      //lcd.print("Temp: ");
      lcd.setCursor(6, 0);
      //lcd.print(fahrenheit);
      lcd.setCursor(0, 1);
      p.Plot();
      /*
      lcd.write(byte(0));
      lcd.write(byte(1));
      lcd.write(byte(2));
      lcd.write(byte(3));
      lcd.write(byte(4));
      lcd.write(byte(5));
      lcd.write(byte(6));
      lcd.write(byte(7));
      */

  /* Insert the Averaged Time into the Queue to Graph */
  /*unsigned long currentTime = millis();
  if (currentTime - previousTime < interval) {
    numTemps++;
    currentSum += fahrenheit;
  }

  if (currentTime - previousTime > interval) {
    previousTime = currentTime;
    
    if (isFull()){
      removeData();
    }
    
    insert(fahrenheit);
    //insert (currentSum / 1.0*numTemps);
    numTemps = 0;
    currentSum = 0;
    for (int i = 0; i < MAX; i++) {
      //Serial.print(intArray[i]);
      //Serial.print(" ");
    }
    //Serial.println(" ");    
  }
  */
}






