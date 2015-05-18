// This #include statement was automatically added by the Spark IDE.
#include "TimeAlarms/TimeAlarms.h"

int pinLed = D3;
int pinRelay = D1;
int pinBTN = D0;

bool isOn = false;
bool isLocked = false;



void setup() {
    pinMode(pinLed, OUTPUT);
    pinMode(pinRelay, OUTPUT);
    pinMode(pinBTN, INPUT);
   // attachInterrupt(pinBTN, btnPressed, CHANGE);
    Spark.function("encender", encender);
    Spark.function("apagar", apagar);
}

void loop() {
    if(digitalRead(pinBTN)==HIGH){
        switchPower();
    }
}


int encender(String args){
    setPower(true);
    isLocked = false;
    return 1;
}

int apagar(String args){
    setPower(false);
    isLocked = false;
    return 1;
}

void setPower(bool ON){
    if (ON){
        digitalWrite(pinRelay,HIGH);
        digitalWrite(pinLed,HIGH);
    } else {
        digitalWrite(pinRelay,LOW);
        digitalWrite(pinLed,LOW);
    }
}

void switchPower(){
    if (isLocked){
        return;
    }
    isLocked = true;
    if (isOn){
        isOn = !isOn;
        setPower(false);
    } else {
        isOn = !isOn;
        setPower(true);
    }
    delay(1000);
    isLocked = false;
}

void btnPressed(){
    switchPower();
}
