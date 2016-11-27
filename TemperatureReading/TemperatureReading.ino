const int sensorPin = A0;
const float baselineTemp = 20.0;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
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

  
  
}
