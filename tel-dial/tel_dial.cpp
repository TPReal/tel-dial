#include "Arduino.h"

#include <Keyboard.h>

const byte PIN_YELLOW=PIN_A0;
const byte PIN_RED=PIN_A1;
const byte PIN_GREEN=PIN_A2;

const int MODE_NUM=1;
const int MODE_ASCII=2;
const int NUM_MODES=2;

const int SERIAL_INIT_WAIT_TIME_MILLIS=3000;

bool DEBUG=true;

int mode;

int asciiCount;
int asciiVal;

void initMode(int m){
  if(DEBUG){
    SerialUSB.print("Mode ");
    SerialUSB.println(m);
  }
  if(mode==MODE_ASCII)
    Keyboard.releaseAll();
  mode=m;
  if(mode==MODE_ASCII){
    asciiCount=0;
    asciiVal=0;
  }
}

int getMinC(int v){
  if(v<=2)
    return 4;
  if(v<10)
    return 2;
  if(v<=25)
    return 3;
  if(v<100)
    return 2;
  return 3;
}

bool processAscii(int c,int v){
  int lZeros=c-getMinC(v);
  if(!lZeros){
    if(DEBUG){
      SerialUSB.print("Print ");
      SerialUSB.println(v);
    }
    Keyboard.write(v);
    Keyboard.releaseAll();
    return true;
  }
  if(lZeros>=2){
    if(DEBUG){
      SerialUSB.print("Press ");
      SerialUSB.print(v);
      SerialUSB.println(", Release all");
    }
    Keyboard.press(v);
    return true;
  }
  return false;
}

void dialled(byte d){
  if(mode==MODE_NUM){
    if(DEBUG){
      SerialUSB.print("Print ");
      SerialUSB.println(d);
    }
    Keyboard.write('0'+d);
  }else if(mode==MODE_ASCII){
    asciiCount++;
    asciiVal=10*asciiVal+d;
    if(processAscii(asciiCount,asciiVal)){
      asciiCount=0;
      asciiVal=0;
    }
  }
}

void optionDialled(int option){
  if(DEBUG){
    SerialUSB.print("Option dialled: ");
    SerialUSB.println(option);
  }
  if(option<=NUM_MODES)
    initMode(option);
}

void pulsed(int p){
  if(p<=10)
    dialled(p%10);
  else{
    int option=19-p;
    if(option>=1&&option<=8)
      optionDialled(option);
    else
      if(DEBUG){
        SerialUSB.print("Pulses: ");
        SerialUSB.println(p);
      }
  }
}

void setup() {
  if(DEBUG){
    SerialUSB.begin(9600);
    while(!SerialUSB)
      if(millis()>=SERIAL_INIT_WAIT_TIME_MILLIS){
        DEBUG=false;
        break;
      }
    SerialUSB.print("Serial USB established in ");
    SerialUSB.print(millis());
    SerialUSB.println("ms");
  }
  pinMode(PIN_YELLOW,INPUT_PULLUP);
  pinMode(PIN_GREEN,INPUT_PULLUP);
  pinMode(PIN_RED,OUTPUT);
  digitalWrite(PIN_RED,LOW);
  Keyboard.begin();
  initMode(MODE_NUM);
}

void loop() {
  if(digitalRead(PIN_YELLOW)==LOW){
    int p=0;
    byte prevG=LOW;
    delay(20);
    while(digitalRead(PIN_YELLOW)==LOW){
      byte g=digitalRead(PIN_GREEN);
      if(g>prevG)
        p++;
      prevG=g;
      digitalWrite(LED_BUILTIN,!g);
      delay(10);
    }
    digitalWrite(LED_BUILTIN,HIGH);
    if(p)
      pulsed(p);
  }
  delay(5);
}
