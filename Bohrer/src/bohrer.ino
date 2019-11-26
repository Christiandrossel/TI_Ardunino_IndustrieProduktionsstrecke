#include <LiquidCrystal.h>

LiquidCrystal lcd(11, 12, 2, 3, 4, 5);
enum State {READY, WORKING};
State state = READY;
//total working time in seconds
int duration = 5;
int timeElapsed = 0;
const int switchStatePin = 13;

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
    // set display size
    lcd.begin(16, 2);
    lcd.createChar(0,bar);
    pinMode(switchStatePin, INPUT);
}

void loop()
{
    if(digitalRead(switchStatePin)){
      state = WORKING;  
    }
    if(state == READY){
        delay(500);
        printReady();  
    }else if (state == WORKING){
      printWorking();
      delay(1000);
      timeElapsed++;
      if (timeElapsed >= duration){
        printWorking();
        state = READY;
        timeElapsed = 0;
      }
    }
}
