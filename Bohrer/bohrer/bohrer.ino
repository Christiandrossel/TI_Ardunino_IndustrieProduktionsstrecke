enum state {BUSY, FREE};
state State = FREE;
char message; //char that stores the incoming message

void setup()
{
 // pinMode(4,INPUT); 
 // Serial.begin(38400); // Default communication rate of the Bluetooth module
 Serial.begin(9600);  //set Baud rate
}

void loop(){

 if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    message = Serial.read(); // Reads the data from the serial port
    Serial.print(message); //sends message back, acknowledgement of receipt
 
 
    if(message=='f') //set state to free when a f was received
    {
      State = FREE;
    }
    if(message=='r') //set state to busy for a while if an r was received
    {
      State = BUSY;
          delay(5000); //simulate working time...
      //delay(random(10000,20000));
      State = FREE;
    }
    if (message!='f'&&message!='b'&&message!='r') //should not occur
    {// Do something if the message doesn't match the expectations
    }
    
  delay(500); //delay
  
 }

}
    
