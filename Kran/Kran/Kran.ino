#include <Servo.h>
Servo myServo;
const int sensorPin = A0;   //Photowiederstand     
const int redLED = 3;       //an den Digital PMW Nummer 3
const int greenLED = 2;     //an den Digital PMW Nummer 2
int angle =0;               //der Winkelwert für den ServoMotor
int sensorValue, oldValue, threshold; //treshhold = Schwellenwert


void ckeckSensor();
void _calcThreshold();
boolean checkChange(int val, int diff);

void setup() {
  
  myServo.attach(9);    //Servo intialisieren
  Serial.begin(9600);   //Serial Port festlegen (ComputerMonitor)

  pinMode(2, OUTPUT);   //LEDs setzen und ausschalten
  pinMode(3, OUTPUT);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);

  myServo.write(angle);   //Servomotor auf angle Wert setzen
  
  _calcThreshold();     //Photowiederstand Kalibrieren
}

void loop() {
  sensorValue = analogRead(sensorPin);      //Wert von Photowiederstand holen
  delay(5);                                 //Wartezeit von 5 ms

  Serial.print("SenorValue: ");             //Serial Ausgabe
  Serial.print(sensorValue);
  Serial.print("\n");

  checkSensor();                            //Überprüft Sonsor veränderungen
  
  delay(50);

  
}

/*Überprüft anhand des sensorValue und treshhold ob Roboter davor steht oder nicht*/
void ckeckSensor(){
  /*Sensor erkennt Roboter*/
  if(sensorValue < threshold && checkChange(sensorValue, 10)){
    angle=90;
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    myServo.write(angle);
    delay(5000);
  }
  /*Wenn kein Roboter vor Sensor ist*/
  else{
    if(checkChange(sensorValue, 10)){
      angle=0;
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
      myServo.write(angle);
    }
  }
}

/*Schwellenwert einstellen bzw. Photowiederstand auf Umgebaungslicht Kalibrieren*/
void _calcThreshold(){
  int maxVal=0;
  int minVal = 1023;
  for(int i=0; i<50; i++){      //50 Durchläufe
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
  threshold= minVal + ((maxVal - minVal)/2);    //Schwellenwert einstellen
}

/*Toleranzwert festlegen */
boolean checkChange(int val, int diff){
  if(val != oldValue){
  	if((oldValue - diff) < val || (oldValue + diff) > val){
  		oldValue = val;
  		return true;
  	}
  }
  return false;
}
	
