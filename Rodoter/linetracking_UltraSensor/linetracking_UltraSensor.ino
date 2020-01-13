#include <Servo.h>
Servo myServo;  // create a servo object
 
//rechter Motor 
int MotorRight1=5; //rückwärts
int MotorRight2=6; // vorwärts
//Linker Motor 
int MotorLeft1=10; //rückwärts
int MotorLeft2=11; // vorwärts

// Ultrasensoren in Gestalt der Rodoteraugen 
#define echoPin 12 // Echo Pin
#define trigPin 13 // Trigger Pin
int const potPin = A0; // analog pin used to connect the potentiometer
long duration, distance; // Variablen für die Distanz

// Linetracking Variablen
const int SensorLeft = 7;  // pin for sensor on the left
const int SensorMiddle= 4 ;// pin for sensor in the middle  
const int SensorRight = 3;// pin for sensor on the right 
int SL; // left sensor status
int SM; // middle sensor status 
int SR; // right sensor status

//Variable für die Werte vom Server
char server; 
// 0 mache eine Pause
// 1 gehe nach rechts
// 2 gehe nach links
// R gehe gerade aus

//Rodoterzustände
enum rodoterstate {GO_TO_CRANE,GO_TO_CROSSROAD,GO_TO_DRILL};
rodoterstate RodoterState = GO_TO_CRANE;

// Bildschirmausgabe aktivieren(true)/deaktivieren(false)
bool activate_console_output=false;

void setup(){
  Serial.begin(9600);
  myServo.attach(9); // attaches the servo on pin 9 to the servo object
  pinMode(MotorRight1, OUTPUT); // pin  5 (PWM) 
  pinMode(MotorRight2, OUTPUT); // pin  6 (PWM) 
  pinMode(MotorLeft1, OUTPUT); // pin  10 (PWM) 
  pinMode(MotorLeft2, OUTPUT); // pin  11 (PWM) 
  pinMode(SensorLeft, INPUT); // define left sensor
  pinMode(SensorMiddle, INPUT);// define middle sensor  
  pinMode(SensorRight, INPUT); // define right sensor
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
}

void loop(){
  
  server=Serial.read();
  
  myServo.write(90);
  SL = digitalRead(SensorLeft);
  SM = digitalRead(SensorMiddle);
  SR = digitalRead(SensorRight); 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58.2;
  if(activate_console_output)
    start_console_output();
  if(distance > 5){
    follow_line();
  }
  else{
    digitalWrite(MotorLeft1,LOW);
    digitalWrite(MotorLeft2,LOW);
    digitalWrite(MotorRight1,LOW);
    digitalWrite(MotorRight2,LOW);
  }
  switch(RodoterState){
    case GO_TO_CRANE:
      if(breakpoint_recognized()){
        Serial.print('c');
        delay(1000);
      }
      if(server=='r'){
        digitalWrite(MotorLeft1,LOW);
        digitalWrite(MotorLeft2,HIGH);
        digitalWrite(MotorRight1,LOW);
        digitalWrite(MotorRight2,HIGH);
        Serial.print('r');
        RodoterState = GO_TO_CROSSROAD;
        delay(1000);
      }
      break;
    case GO_TO_CROSSROAD:
    // schicke r in case
    // lösche r in breakpoint_recognized()
      if(breakpoint_recognized()){
        Serial.print('d');
        delay(1000);
      }
      switch(server){
        case '0':
          digitalWrite(MotorLeft1,LOW);
          digitalWrite(MotorLeft2,LOW);
          digitalWrite(MotorRight1,LOW);
          digitalWrite(MotorRight2,LOW);
          Serial.print('0');
          //RodoterState = GO_TO_DRILL;
          delay(700);
          break;
        case '1':
          digitalWrite(MotorLeft1,LOW); 
          digitalWrite(MotorLeft2,HIGH);
          digitalWrite(MotorRight1,LOW);
          digitalWrite(MotorRight2,LOW);
          Serial.print('1');
          RodoterState = GO_TO_DRILL;
          delay(2000);
          break;
        case '2':
          digitalWrite(MotorLeft1,LOW);
          digitalWrite(MotorLeft2,LOW);
          digitalWrite(MotorRight1,LOW);
          digitalWrite(MotorRight2,HIGH);
          Serial.print('2');
          RodoterState = GO_TO_DRILL;
          delay(2000);
          break;
      }
      break; 
    case GO_TO_DRILL:       
      if(server=='r'){
        digitalWrite(MotorLeft1,LOW);
        digitalWrite(MotorLeft2,HIGH);
        digitalWrite(MotorRight1,LOW);
        digitalWrite(MotorRight2,HIGH);
        Serial.print('r');
        RodoterState = GO_TO_CRANE;
        delay(1000); 
      }
      break;
    }
}
void follow_line(){
  if (SM == HIGH)// middle sensor in black area
  {
    if (SL == LOW & SR == HIGH) // black on left, white on right, turn left
    {
      digitalWrite(MotorRight1,LOW);
      digitalWrite(MotorRight2,HIGH);
      digitalWrite(MotorLeft1,LOW);
      digitalWrite(MotorLeft2,LOW);
    }
    else if (SR == LOW & SL == HIGH) // white on left, black on right, turn right
    {
      digitalWrite(MotorLeft1,LOW);
      digitalWrite(MotorLeft2,HIGH);
      digitalWrite(MotorRight1,LOW);
      digitalWrite(MotorRight2,LOW);
    }
    else // white on both sides, going forward
    {
      digitalWrite(MotorRight1,LOW);
      digitalWrite(MotorRight2,HIGH);
      digitalWrite(MotorLeft1,LOW);
      digitalWrite(MotorLeft2,HIGH);
    }
  }
  else // middle sensor on white area
  {
    if (SL== LOW & SR == HIGH)// black on left, white on right, turn left
    {
      digitalWrite(MotorRight1,LOW);
      digitalWrite(MotorRight2,HIGH);
      digitalWrite(MotorLeft1,LOW);
      digitalWrite(MotorLeft2,LOW);
    }
    else if (SR == LOW & SL == HIGH) // white on left, black on right, turn right
    {
      digitalWrite(MotorLeft1,LOW);
      digitalWrite(MotorLeft2,HIGH);
      digitalWrite(MotorRight1,LOW);
      digitalWrite(MotorRight2,LOW);
    }
    else // all white, stop
    {
      digitalWrite(MotorLeft1,LOW);
      digitalWrite(MotorLeft2,LOW);
      digitalWrite(MotorRight1,LOW);
      digitalWrite(MotorRight2,LOW);
    }
  }
} 
boolean breakpoint_recognized(){
  if(SM==LOW && SR==LOW && SL==LOW)
    return true;
  else
    return false;
}
void start_console_output(){
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("Rodoterstate: ");
  if(RodoterState == 0)
    Serial.println("GO_TO_CRANE");
  else if(RodoterState == 1)
    Serial.println("GO_TO_CROSSROAD");
  else if(RodoterState == 2)
    Serial.println("GO_TO_DRILL");
  Serial.print("server: ");
  Serial.println(server);
  delay(2000);
}
