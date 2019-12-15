#include <Servo.h>
#include "pitches.h"

Servo myServo;

const int photoSensor = A1; //Photowiederstand
const int sensorEinst = A0; //Drehwiederstand
const int piezo = 8; //Tongeber
const int greenLED = 3; //LED
int lied = 1;

int threshold; //Schwellenwert für Photowiederstand
int thresholdPlus; //Schwellenwert nach Korrektur
int sensorValue; //Wert vom Photowiederstand
int differenz; 
int einstValue;

//Melody von Mario
int melody1[] = {
  NOTE_E4, NOTE_E4, NOTE_E4, 0, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_GS3,
  NOTE_C4, 0, NOTE_GS3, 0, NOTE_E3, 0, NOTE_A3, 0, NOTE_B3, 0, NOTE_AS3, NOTE_A3, 
  NOTE_GS3, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_G4, 0, NOTE_E4, 0, NOTE_C4, NOTE_D4, NOTE_B3
};

//Tonlänge: 4 viertelNote, 8 achtelnote....
//zu Mario
int noteDurations1[] ={
  16, 8, 16, 16, 16, 8, 4, 4,
  8, 16, 16, 8, 8, 16, 16, 16, 16, 16, 16, 8,
  12, 12, 12, 8, 16, 16, 16, 16, 16, 16, 16, 16, 8
};

//Erkannt?
int melody2[] = {
  NOTE_DS3, 
  NOTE_E3, 0, NOTE_FS3, NOTE_G3, 0, NOTE_DS3, 
  NOTE_E3, NOTE_FS3, NOTE_G3, NOTE_C4, NOTE_B3, NOTE_E3, NOTE_G3, NOTE_B3, 
  NOTE_AS3, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_E3, NOTE_D3, NOTE_E3, 
  NOTE_E3,  
  };

//Tonlänge: 4 viertelNote, 8 achtelnote....
int noteDurations2[] ={
  16, 
  4, 8, 16, 4, 8, 16, 
  8, 16, 8, 16, 8, 16, 8, 16, 
  2, 14, 14, 14, 14, 14, 14, 
  2
};



void _calcThreshold();
void checkSensor();


void setup() {
  myServo.attach(9);    //Servo intialisieren
  Serial.begin(9600);   //Serial Port festlegen (ComputerMonitor)

  pinMode(greenLED, OUTPUT);   //LEDs setzen und ausschalten
  digitalWrite(greenLED, LOW);

  myServo.write(91);   //Servomotor auf Startzustand setzen
  
  _calcThreshold();     //Photowiederstand Kalibrieren
  Serial.print(threshold);

}

void loop() {
  sensorValue = analogRead(photoSensor); //Wert einlesen
  einstValue = analogRead(sensorEinst);
  differenz = map(einstValue, 0, 1023, -100, 100);
  delay(5);

  // debug info
  /*Serial.print("SensorValue: ");             //Serial Ausgabe
  Serial.print(sensorValue);
  Serial.print(" - ");
  Serial.print("Einst: ");             
  Serial.print(differenz);
  Serial.print("\n");*/
  
  thresholdPlus = threshold + differenz;
  checkSensor();
  delay(50);
  
}

/*Überprüft anhand des sensorValue und treshhold ob Roboter davor steht oder nicht*/
void checkSensor(){
  /*Sensor erkennt Roboter (Kran besetzt)*/
  if(sensorValue < thresholdPlus){
    myServo.write(1);
    digitalWrite(greenLED, HIGH);
    Serial.print('1');            //Sende an Server eine 1 für Status besetzt
    tonspiel();
    delay(1000);    //Kran wird beladen
    myServo.write(91);
    digitalWrite(greenLED, LOW);
    delay(5000); //warten bis Rodoter wegefahren ist
  }
  /*Wenn kein Roboter vor Sensor ist (Kran ist frei)*/
  else{
      digitalWrite(greenLED, LOW);
      Serial.print('0');        //Sende an Server eine 0 für nicht besetzt
  }
}


//Schwellenwert berechnen und einstellen
void _calcThreshold() {
  int maxVal=0;
  for(int i=0; i<50; i++){      //50 Durchläufe
    int currentVal = analogRead(photoSensor);   
    maxVal += currentVal;

    delay(50);
    digitalWrite(greenLED, HIGH);
    delay(50);
    digitalWrite(greenLED, LOW);
  }
  threshold = maxVal / 50;    //Schwellenwert einstellen
}

//spiele die Melodie ab
void tonspiel() {
  if(lied == 1){
    for (int thisNote = 0; thisNote < 33; thisNote++) {
      //Geschwindigkeit der Melody
      int noteDuration = 1500 / noteDurations1[thisNote];
      tone(piezo, melody1[thisNote], noteDuration);
    
      //Pause zwischen den Noten, ca 30 Prozent der Notenlänge
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
    
      // Ton ausschalten
      noTone(piezo);
    }
    lied = 2;
  }else if(lied == 2){
    for (int thisNote = 0; thisNote < 23; thisNote++) {
      //Geschwindigkeit der Melody
      int noteDuration = 1500 / noteDurations2[thisNote];
      tone(piezo, melody2[thisNote], noteDuration);
    
      //Pause zwischen den Noten, ca 30 Prozent der Notenlänge
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
    
      // Ton ausschalten
      noTone(piezo);
    }
    lied = 1;  
  }
}
