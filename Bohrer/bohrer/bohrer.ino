#include <LiquidCrystal.h>

LiquidCrystal lcd(11, 12, 2, 3, 4, 5);
enum state {BUSY, FREE};
state State = FREE;
bool reportState = false;
//total working time in seconds
int duration = 5;
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

void printWorking(){
    int barSize = (16 * timeElapsed)/duration;
    lcd.clear();
    lcd.print("Fortschritt:");
    lcd.setCursor(0,1);
    for (int i = 0; i < barSize; i++){
      lcd.write(byte(0));
    }
}

void setup()
{
 // pinMode(4,INPUT); 
 // Serial.begin(38400); // Default communication rate of the Bluetooth module
 Serial.begin(9600);  //set Baud rate
  // set display size
  lcd.begin(16, 2);
  // create custom char bar for lcd
  lcd.createChar(0,bar);
}

void loop(){

  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    if(Serial.read()=='b') //set state to busy
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
    
