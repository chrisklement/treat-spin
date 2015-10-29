// Piezo
int beepPin = D0;
int beep = 0;

// DC-Motor
int analogInPin = A4;
int analogOutPin = D2;

int sensorValue = 0;
int outputValue = 0;

// Servo
int servoPin = D1;
int angle = 0; 
Servo servo;

// Spark function Settings
int spinOn = false;
int spinToggle(String command);

// Set function for IFTTT
void setup(){
  Serial.begin(9600);
  Spark.function("spin",spinToggle);
  servo.attach(servoPin);
  
  // Output DC-Motor
  pinMode(analogOutPin, OUTPUT);
  digitalWrite(analogOutPin, HIGH);
  }

void loop(){
  // Nothing to do here
  }

int spinToggle(String command) {
  
  spinOn = true;
  
  if (spinOn == true){    

    if (command=="on") {
      
      // play 3 notes on pin D2 for 300 ms:
      for(beep = 0; beep < 3; beep++){
        tone(beepPin, 440, 100);
        delay(1000);
      }
      sensorValue = analogRead(analogInPin);
      outputValue = map(sensorValue, 0, 4095, 0, 255);
      analogWrite(analogOutPin, outputValue);
    
      // scan from 0 to 180 degrees   
      for(angle = 160; angle > 40; angle--){
        servo.write(angle);
        //delay(5);     
      }
      
      delay(2000);
    
      // scan back from 180 to 0 degrees
      for(angle = 40; angle < 160; angle++){
        servo.write(angle);
        //delay(5);
      }
      digitalWrite(analogOutPin, HIGH);
      return 1;
    
    }
    
    spinOn = false;
    
  }
  
  else return -1;

}
