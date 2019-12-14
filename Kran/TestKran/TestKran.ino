#include <Servo.h>

Servo myServo;

const int Photo = A1;
const int Einst = A0;
const int LED = 3;
const int Piezo = 8;


int nahe = 0;
int umgebung = 0;


int melody[] = {
  330, 330, 330, 0, 262, 330, 392, 208,
  262, 0, 208, 0, 165, 0, 220, 0, 247, 0, 233, 220, 
  208, 330, 392, 440, 349, 392, 0, 330, 0, 262, 294, 247
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  16, 8, 16, 16, 16, 8, 4, 4,
  8, 16, 16, 8, 8, 16, 16, 16, 16, 16, 16, 8,
  12, 12, 12, 8, 16, 16, 16, 16, 16, 16, 16, 16, 8
};

void setup() {
  pinMode(LED,OUTPUT);
  myServo.attach(9);
  myServo.write(90);
  delay(15);
  Serial.begin(9600);

  
}


void loop() {
  nahe = analogRead(Photo);
  umgebung = analogRead(Einst);
  Serial.print("Drehwiederstand: ");
  Serial.print(umgebung);
  Serial.print("\t Nahe: ");
  Serial.print(nahe);
  Serial.print("\n\n");

  
  if(nahe < umgebung){
    digitalWrite(LED,HIGH);
    myServo.write(0);
    delay(500);
    tonspiel();
    myServo.write(90);
  }else{
    digitalWrite(LED,LOW);
  }
} 

void tonspiel() {
  for (int thisNote = 0; thisNote < 33; thisNote++) {
    int noteDuration = 1500 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }

}
