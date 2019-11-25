int MotorRight1=5;
int MotorRight2=6; 
int MotorLeft1=10;
int MotorLeft2=11;
#define echoPin 12 // Echo Pin
#define trigPin 13 // Trigger Pin
long duration, distance; // Duration used to calculate distance
const int SensorLeft = 7;  // pin for sensor on the left
const int SensorMiddle= 4 ;// pin for sensor in the middle  
const int SensorRight = 3;// pin for sensor on the right 
int SL; // left sensor status
int SM; // middle sensor status 
int SR; // right sensor status

int server = 1;

void setup()
{
  Serial.begin(9600);
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


void loop()
{
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
  if(distance > 5)
  {
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
        
  // Serverwerte werden ausgewertet und Rodoter bewegt sich in entsprechender Richtung
  
        if(server == 1){
          digitalWrite(MotorLeft1,LOW);
          digitalWrite(MotorLeft2,HIGH);
          digitalWrite(MotorRight1,LOW);
          digitalWrite(MotorRight2,LOW);
          delay(1000);
          server = 0;
        }
         if(server == 2){
          digitalWrite(MotorLeft1,LOW);
          digitalWrite(MotorLeft2,LOW);
          digitalWrite(MotorRight1,LOW);
          digitalWrite(MotorRight2,HIGH);
          delay(1000);
          server = 0;
        }
         if(server == 3){
          digitalWrite(MotorLeft1,LOW);
          digitalWrite(MotorLeft2,HIGH);
          digitalWrite(MotorRight1,LOW);
          digitalWrite(MotorRight2,HIGH);
          delay(1000);
          server = 0;
        }
      }
    }
  }else
  {
    digitalWrite(MotorLeft1,LOW);
    digitalWrite(MotorLeft2,LOW);
    digitalWrite(MotorRight1,LOW);
    digitalWrite(MotorRight2,LOW);
  }
}
 
