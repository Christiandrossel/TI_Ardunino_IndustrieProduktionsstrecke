char blueToothVal; //Werte sollen per Bluetooth gesendet werden
char lastValue;   //speichert den letzten Status der LED (on/off) 
 
void setup(){
 Serial.begin(9600);  //serieller Monitor wird gestartet, Baudrate auf 9600 festgelegt
 pinMode(13,OUTPUT);  //PIN 13 wird als Ausgang festgelegt
}
 
void loop(){
  if(Serial.available()) //wenn Daten empfangen werden...      
{
    blueToothVal=Serial.read();//..sollen diese ausgelesen werden
  }
  if (blueToothVal=='1') //wenn das Bluetooth Modul eine „1“ empfängt..
  {
    /**
     * TODO
     */
    
    digitalWrite(13,HIGH);   //...soll die LED leuchten
    if (lastValue!='1') //wenn der letzte empfangene Wert keine „1“ war...
      Serial.println(F("LED is on")); //..soll auf dem Seriellen Monitor „LED is on“ angezeigt werden
    lastValue=blueToothVal;
  }
  else if (blueToothVal=='0') //wenn das Bluetooth Modul „0“ empfängt...
  {
    /**           
     *  TODO
     */
    digitalWrite(13,LOW);  //..soll die LED nicht leuchten
    if (lastValue!='0')  //wenn der letzte empfangene Wert keine „0“ war...
      Serial.println(F("LED is off")); //..soll auf dem seriellen Monitor „LED is off“ angezeigt werden 
    lastValue=blueToothVal;
  }
 }
