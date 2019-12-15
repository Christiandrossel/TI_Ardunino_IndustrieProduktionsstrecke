#include <Servo.h>
Servo myServo;
const int sensorPin = A0;   //Photowiederstand     
const int redLED = 3;       //an den Digital PMW Nummer 3
const int greenLED = 2;     //an den Digital PMW Nummer 2
int angle =0;               //der Winkelwert für den ServoMotor
int sensorValue, oldValue, threshold; //treshhold = Schwellenwert

char blueToothVal; //Werte die per Bluetooth empfangen werden
char lastValue;   //speichert den letzten Status (on/off)
char sendBluetoothVal; 

void checkSensor();
void _calcThreshold();
boolean checkChange(int val, int diff);
int bluethoothClient();
boolean openGate();
boolean closeGate();

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
  bluethoothClient();
  delay(50);

  
}

/*Überprüft anhand des sensorValue und treshhold ob Roboter davor steht oder nicht*/
void checkSensor(){
  /*Sensor erkennt Roboter (Kran besetzt)*/
  if(sensorValue < threshold && checkChange(sensorValue, 10)){
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    Serial.print('1');						//Sende an Server eine 1 für Status besetzt
	delay(5000);    //Kran wird beladen
    openGate();   //öffne Schranke
    delay(5000);            //halte sie offen damit Rodoter Zeit hat um weiter zu fahren
  }
  /*Wenn kein Roboter vor Sensor ist (Kran ist frei)*/
  else{
    if(checkChange(sensorValue, 10)){
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
	  Serial.print('0');				//Sende an Server eine 0 für nicht besetzt
      closeGate(); //Schließe Schranke
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

/*Client Modul das Daten Empfängt und darauf reagiert*/
int bluethoothClient(){
  if(Serial.available()) //wenn Daten empfangen werden...      
{
    blueToothVal=Serial.read();//..sollen diese ausgelesen werden
  }
  if (blueToothVal=='1') //öffne Schranke
  {
    openGate();                   //öffne Schranke
    delay(5000);
    digitalWrite(greenLED,HIGH);   // Grüne LED soll leuchten
    digitalWrite(redLED, LOW);
    
    if (lastValue!='1') //wenn der letzte empfangene Wert keine „1“ war...
      //Serial.println(F("LED is on")); //..soll auf dem Seriellen Monitor „LED is on“ angezeigt werden
    lastValue=blueToothVal;
    return 1;
  }
  else if (blueToothVal=='0') //wenn das Bluetooth Modul „0“ empfängt...
  {
    digitalWrite(greenLED,LOW);  //..soll die LED nicht leuchten
    digitalWrite(redLED, HIGH);  // rote LED soll leuchten
    closeGate();
    
    if (lastValue!='0')  //wenn der letzte empfangene Wert keine „0“ war...
      Serial.println(F("LED is off")); //..soll auf dem seriellen Monitor „LED is off“ angezeigt werden 
    lastValue=blueToothVal;
    return 0;
  }
  return -1;
}

boolean openGate(){
  angle=91;
  myServo.write(angle);
}

boolean closeGate(){
  angle=0;
  myServo.write(angle);
}

	
