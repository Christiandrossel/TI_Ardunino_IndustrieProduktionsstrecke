#include <LiquidCrystal.h>

const int photoSensor = A0; //Photowiederstand
const int sensorEinst = A1; //Drehwiederstand
bool rodoter = false; //Rodoter anwesend?
int threshold; //Schwellenwert für Photowiederstand
int thresholdPlus; //Schwellenwert nach Korrektur
int sensorValue; //Wert vom Photowiederstand
const int greenLED = 8; //LED
int differenz; 
int einstValue;


LiquidCrystal lcd(11, 12, 2, 3, 4, 5);
enum state {BUSY, FREE};
state State = FREE;
bool reportState = false;
//total working time in seconds
int duration = 12;
int timeElapsed = 0;
// full bar charackter
byte bar[8]={
  B1111,
  B1111,
  B1111,
  B1111,
  B1111,
  B1111,
  B1111,
  B1111
};

void printReady(){
    lcd.clear();
    lcd.print("Bereit");
}

void printTest(){
    lcd.clear();
    lcd.print("TEST");
}

void printBusy(){
    lcd.clear();
    lcd.print("Waiting for Rodo");
}


void printWorking(){
    int barSize = (16 * timeElapsed)/duration;
    lcd.clear();
    lcd.print("Fortschritt:");
    lcd.setCursor(0,1);
    for (int i = 0; i < barSize; i++){
      lcd.write(byte(0));
    }
}

//---------------------------------
/*Überprüft anhand des sensorValue und treshhold ob Roboter davor steht oder nicht*/
void checkSensor(){
  /*Sensor erkennt Roboter (Kran besetzt)*/
  if(sensorValue < thresholdPlus){

    digitalWrite(greenLED, HIGH);
    rodoter = true;

    delay(100);    //Kran wird beladen

     digitalWrite(greenLED, LOW);
    //delay(5000); //warten bis Rodoter wegefahren ist
  }
  /*Wenn kein Roboter vor Sensor ist (Kran ist frei)*/
  else{
    digitalWrite(greenLED, LOW);

        rodoter = false;
        return;
      }
      //Serial.print('r');
    }
//  }
//}


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
//----------------------------------------



void setup()
{
 // pinMode(4,INPUT); 
 // Serial.begin(38400); // Default communication rate of the Bluetooth module
 Serial.begin(9600);  //set Baud rate
  // set display size
  lcd.begin(16, 2);
  // create custom char bar for lcd
  lcd.createChar(0,bar);

  pinMode(greenLED, OUTPUT);   //LEDs setzen und ausschalten
  digitalWrite(greenLED, LOW);
_calcThreshold();
  
}

void loop(){
  
//
//
//
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
  //delay(50);
  //
  //
  //
 

  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    if(Serial.read()=='r') //set state to busy
    {
      State = BUSY;
    }
 }
  if(State == FREE){
    if (!reportState){
      Serial.print('r');
      reportState = true;
    }
    delay(500);
    printReady();
  }else if (State == BUSY){
    
    //hier sensor checken:
    //printBusy();
//while(rodoter == false){

int count = 1;

  while(count = 1){


sensorValue = analogRead(photoSensor); //Wert einlesen
  einstValue = analogRead(sensorEinst);
    
    
    lcd.clear();
    lcd.print("rodo==false");
// rodoter = true;
 //checkSensor();

   if(sensorValue < thresholdPlus){

    digitalWrite(greenLED, HIGH);
    rodoter = true;
    count = 0;

    delay(10);    //Kran wird beladen

     digitalWrite(greenLED, LOW);
    //delay(5000); //warten bis Rodoter wegefahren ist

    break;
  }
  
 delay(200);
 //if (rodoter==true) {count = 0;}
  //checkSensor();
//if (rodoter == true){printTest();break;};

}
    //-------------------
    printWorking();
    delay(1000);
    timeElapsed++;
    if (timeElapsed >= duration){
      printWorking();
      State = FREE;
      timeElapsed = 0;
      reportState = false;
    }
  }
}
