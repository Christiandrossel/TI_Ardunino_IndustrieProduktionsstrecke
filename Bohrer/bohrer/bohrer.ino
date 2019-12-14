//Zustände:
//b = busy / beschäftigt
//f = free / frei

char state = 'f'; //initial state is free
char message = 'f'; //string that stores the incoming message

void setup()
{
  Serial.begin(9600); //set baud rate



}

void loop()
{
  while(Serial.available())
  {//while there is data available on the serial monitor
    message=char(Serial.read());//store string from serial command
  }
  if(!Serial.available())
  {
    if(message='f')
    {//if state should be free
      Serial.print(message); //show the data
      state = 'f'; //set state = free
    }
     else if(message='b')
    {//if state should be busy
      Serial.print(message); //show the data
      state = 'b'; //set state busy
    }
     else if (message!='f'&&message!='b')
    {//something else...
      Serial.print(message); //show the data
    }
    if (state = 'b'){
      //do something.... (Sound, LED-Color...)
      //wait random between 10-20sec
      delay(random(10000,20000));
      Serial.print('r'); //send r char to server (ready)
      state = 'f';
    }
  }
  delay(500); //delay
}
    
