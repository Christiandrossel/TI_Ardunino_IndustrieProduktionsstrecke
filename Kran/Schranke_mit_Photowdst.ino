#include <Servo.h>
Servo myServo;
const int sensorPin = A0;
const int redLED = 3;
const int greenLED = 2;
int angle =0; 
int sensorValue, oldValue, threshold;


void _calcThreshold();
boolean checkChange(int val, int diff);

void setup() {
  // put your setup code here, to run once:
  myServo.attach(9);
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);

  myServo.write(angle);
  
  _calcThreshold();
}

void loop() {
  sensorValue = analogRead(sensorPin);
  delay(5);

  Serial.print("SenorValue: ");
  Serial.print(sensorValue);
  Serial.print("\n");
  //wenn sensorValue = XY wert dann angle=0 else angle=90;
  if(sensorValue < threshold && checkChange(sensorValue, 10)){
    angle=90;
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
	  myServo.write(angle);
    delay(5000);
  }
  else{
	if(checkChange(sensorValue, 10)){
		angle=0;
		digitalWrite(redLED, HIGH);
		digitalWrite(greenLED, LOW);
		myServo.write(angle);
	}
  }
  
  delay(50);

  
}

void _calcThreshold(){
  int maxVal=0;
  int minVal = 1023;
  for(int i=0; i<50; i++){
    int currentVal = analogRead(sensorPin);
    if(currentVal < minVal)
      minVal = currentVal;
    if(currentVal > maxVal)
      maxVal = currentVal;

      delay(50);
      digitalWrite(redLED, HIGH);
      delay(50);
      digitalWrite(redLED, LOW);
  }
  threshold= minVal + ((maxVal - minVal)/2);
}

boolean checkChange(int val, int diff){
  if(val != oldValue){
  	if((oldValue - diff) < val || (oldValue + diff) > val){
  		oldValue = val;
  		return true;
  	}
  }
  return false;
}
	
