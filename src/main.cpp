/*================================================================

Beschreibung: Füllstandsüberwachung Wasserreservoir
Autor:        Remo Trinkler
Datum:        14.11.2022
Version:      1.0.0

=================================================================*/




#include <Arduino.h>
#include <library_fuellstand.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(trigger, OUTPUT);             //Trigger-Pin des Ultraschallsensors an Pin2 des Arduino-Boards 
  pinMode(echo, INPUT);                 //Echo-Pim des Ultraschallsensors an Pin3 des Arduino-Boards 
  Serial.begin (9600);                  //Serielle kommunikation starten, damit man sich später die Werte am serial monitor ansehen kann.
}


void loop() 
{
digitalWrite(trigger, LOW);             //Hier nimmt man die Spannung für kurze Zeit vom Trigger-Pin, damit man später beim senden des Trigger-Signals ein rauschfreies Signal hat.
delay(5);
digitalWrite(trigger, HIGH);            //Jetzt sendet man eine Ultraschallwelle los.
delay(2);
digitalWrite(trigger, LOW);             //Dann wird der „Ton“ abgeschaltet.


dauer=pulseIn(echo, HIGH);              //Mit dem Befehl „pulseIn“ zählt der Mikrokontroller die Zeit in Mikrosekunden, bis der Schall zum Ultraschallsensor zurückkehrt.
distanz=(dauer/2.0)*0.0350;             //Nun berechnet man die Entfernung in Zentimetern. Man teilt zunächst die Zeit durch zwei (Weil man ja nur eine Strecke berechnen möchte und nicht die Strecke hin- und zurück). Den Wert multipliziert man mit der Schallgeschwindigkeit in der Einheit Zentimeter/Mikrosekunde und erhält dann den Wert in Zentimetern.
hohe=(350-distanz)/100.0;               //Hier wird die Wasserhöhe ermittelt. Gesamthöhe Reservoir-gemessene Distanz/100(Damit man Meter erhält)
fullstand=(hohe*150);                   //Hier wird das Volumen berechnet
curentstand=fullstand;   


if (previousstand > (curentstand+5))    //Hier wird der Wasserverbrauch ermittelt. immer wenn der Wasserstand sinkt wird der wert addiert und gespeichert
    verbrauch= verbrauch+(previousstand-curentstand);
    previousstand=curentstand;


lcd.init();                             //initialisierung des LCD Displays
lcd.backlight();                        //Hintergrundbeleuchung einschalten Display
lcd.setCursor(0,0);                     //der Cursor wird gesetzt. ab wo auf dem Display zu schreiben begonnen wird
lcd.print("Hoehe ");
lcd.print(hohe);
lcd.print("m");
lcd.setCursor(0,1);
lcd.print("Fuellstand ");
lcd.print(fullstand);
lcd.print("m3");
delay(4000);
lcd.clear();                            //Hier wird auf die "2 Seite" geblättert
lcd.setCursor(0,0);
lcd.print("Verbrauch ");
lcd.print(verbrauch);
lcd.print("m3");
delay(4000);
  }
