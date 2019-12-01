# Client Anwendung

Mit diesen Client wird eine Rote LED ein und ausgeschaltet.

## Aufbau

Die LED muss auf Digital PMW Nummer 13 verbunden werden.
Außerdem muss ein 10-kOhm Widerstand hinter der LED platziert werden.

![Aufbau](hc-05-serial_Steckplatine.jpg)

## Verwendung

Um den Client vorerst zu testen gibt es im Google Play Store 
[diese App](https://play.google.com/store/apps/details?id=com.circuitmagic.arduinobluetooth)

Beim Hochladen auf Arduino muss das Bluetooth herausgenommen werden. Sonst erscheint die Fehlermeldung, 
dass der Code nicht hochgeladen werden kann.
Nach dem Hochladen kann man das Modul wieder einsetzen.
Nach dem einstecken sollte eine LED am Bluetoothmodul schnell blinken, das bedeutet,
dass es bereit ist sich mit einem Gerät zu verbinden.
Dazu sucht man im Smartphone unter der Bluetootheinstellung nach den Namen HC-05.

Wenn nach einem **Pin** gefragt wird, so ist dieser meistens **1234**