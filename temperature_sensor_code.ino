//Author: George Boateng
//Title: This program measures the ambient temperature from a temperature sensor connected to an Arduino board and then  
//       turns on 3 LEDs incrementally as the temperature changes in increments of 2 degrees above a baseline temperature

const int sensorPin = A0;  //setting up sensor pin connected to AnalogIn pin 0
const int calibratePin = 13; //setting up pin for on-board LED to indicate callibration
float baselineTemp = 0.0;
int sensorValue = 0; 


void setup(){
  Serial.begin(9600); //opens a serial port
  
  //Set up and initialize output pins connected to the 3 LEDs
  for (int pinNumber = 2; pinNumber< 5; pinNumber++){
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
  
  //Turn on-board LED on to indicate callibration
  pinMode(calibratePin, OUTPUT);
  digitalWrite(calibratePin, HIGH);
  
   //Calibrate during the first five seconds 
  while (millis() < 5000) {
    sensorValue = analogRead(sensorPin);

    // Record the maximum sensor value
    if (sensorValue > baselineTemp) {
      baselineTemp = sensorValue;
    }

  }

  // Signal the end of the calibration period
  digitalWrite(calibratePin, LOW);
}

void loop() {
  //Read the value on sensor pin and store it in a variable
  int sensorVal = analogRead(sensorPin); //Getting input from temp sensor
  
  //Send the sensor value out the serial port
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);

  //Convert the ADC reading to voltage
  float voltage = (sensorVal/1024.0) * 5.0;
  
  // Send the voltage level out the Serial port
  Serial.print(", Volts: ");
  Serial.print(voltage);

  //Convert the voltage to temperature in degrees
  //the sensor changes 10 mV per degree
  //the datasheet says there's a 500 mV offset
  //((volatge - 500mV) times 100)
  Serial.print(", degrees C: ");
  float temperature = (voltage -.5)* 100;
  Serial.println(temperature);
  
  //Turn off the LEDs when the temperature is below the baseline temperature
  if (temperature < baselineTemp){
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  
  //Turn on the first LED when the temperature is increases beyond the baseline temperature by 2-4 degress
  }else if (temperature >= (baselineTemp+2) && temperature < (baselineTemp+4)){
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  
  
  //Turn on the first 2 LEDs when the temperature is increases beyond the baseline temperature by 4-6 degress
  }else if (temperature >= (baselineTemp+4) && temperature < (baselineTemp+6)){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  
  
  //Turn on all the 3 LEDs when the temperature  increases beyond the baseline temperature by 6 or more degress
  }else if (temperature >= (baselineTemp+6)){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
  delay(1);
}


