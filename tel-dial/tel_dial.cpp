#include "Arduino.h"

#include <Keyboard.h>
#include <algorithm>
#include <set>
#include <vector>

const byte PIN_YELLOW=PIN_A0;
const byte PIN_RED=PIN_A1;
const byte PIN_GREEN=PIN_A2;

const int MODE_NUM=1;
const int MODE_ASCII=2;
const int NUM_MODES=2;

const int SERIAL_INIT_WAIT_TIME_MILLIS=3000;

bool SDEBUG=true;

int mode;

struct ASCIIModeData {
  int count;
  int val;
  std::set<int> held;
  std::vector<int> shortHeld;
} ascii;

void initMode(int m){
  if(SDEBUG){
    SerialUSB.print("Mode ");
    SerialUSB.println(m);
  }
  if(mode==MODE_ASCII)
    Keyboard.releaseAll();
  mode=m;
  if(mode==MODE_ASCII){
    Keyboard.releaseAll();
    ascii.count=0;
    ascii.val=0;
    ascii.held.clear();
    ascii.shortHeld.clear();
  }
}

int getMinC(int v){
  if(v<=2)
    return 6;
  if(v<10)
    return 2;
  if(v<=25)
    return 3;
  if(v<100)
    return 2;
  return 3;
}

bool processAscii(int c,int v){
  int minC=getMinC(v);
  int lZeros=c-minC;
  if(SDEBUG){
    SerialUSB.print("[count=");
    SerialUSB.print(c);
    SerialUSB.print(", value=");
    SerialUSB.print(v);
    SerialUSB.print(", lZeros=");
    SerialUSB.print(lZeros);
    SerialUSB.println("]");
  }
  if(lZeros>=0){
    auto heldIter=ascii.held.find(v);
    bool held=heldIter!=ascii.held.end();
    if(held){
      if(SDEBUG){
        SerialUSB.print("Release #");
        SerialUSB.println(v);
      }
      Keyboard.release(v);
      ascii.held.erase(heldIter);
      auto shortHeldIter=std::find(ascii.shortHeld.begin(),ascii.shortHeld.end(),v);
      if(shortHeldIter!=ascii.shortHeld.end())
        ascii.shortHeld.erase(shortHeldIter);
      return true;
    }
    if(!lZeros){
      if(SDEBUG){
        SerialUSB.print("Type #");
        SerialUSB.println(v);
      }
      Keyboard.write(v);
      for(int i=ascii.shortHeld.size()-1;i>=0;i--){
        int toRelease=ascii.shortHeld[i];
        if(SDEBUG){
          SerialUSB.print("Release #");
          SerialUSB.println(toRelease);
        }
        Keyboard.release(toRelease);
        ascii.held.erase(ascii.held.find(toRelease));
      }
      ascii.shortHeld.clear();
      return true;
    }
    if(lZeros==2){
      if(SDEBUG){
        SerialUSB.print("Short hold #");
        SerialUSB.println(v);
      }
      Keyboard.press(v);
      ascii.held.insert(v);
      ascii.shortHeld.push_back(v);
      return true;
    }
    if(lZeros==4){
      if(SDEBUG){
        SerialUSB.print("Hold #");
        SerialUSB.println(v);
      }
      Keyboard.press(v);
      ascii.held.insert(v);
      return true;
    }
  }
  return false;
}

void dialled(byte d){
  if(mode==MODE_NUM){
    if(SDEBUG){
      SerialUSB.print("Print ");
      SerialUSB.println(d);
    }
    Keyboard.write('0'+d);
  }else if(mode==MODE_ASCII){
    ascii.count++;
    ascii.val=10*ascii.val+d;
    if(processAscii(ascii.count,ascii.val)){
      ascii.count=0;
      ascii.val=0;
    }
  }
}

void optionDialled(int option){
  if(option<=NUM_MODES)
    initMode(option);
}

void pulsed(int p){
  if(p<=10){
    int digit=p%10;
    if(SDEBUG){
      SerialUSB.print("Dialled ");
      SerialUSB.println(digit);
    }
    dialled(digit);
  }else{
    int option=19-p;
    if(option>=1&&option<=8){
      if(SDEBUG){
        SerialUSB.print("Dialled option ");
        SerialUSB.println(option);
      }
      optionDialled(option);
    }else
      if(SDEBUG){
        SerialUSB.print("Pulses: ");
        SerialUSB.println(p);
        SerialUSB.print(", ignored");
      }
  }
}

void setup() {
  if(SDEBUG){
    SerialUSB.begin(9600);
    while(!SerialUSB)
      if(millis()>=SERIAL_INIT_WAIT_TIME_MILLIS){
        SDEBUG=false;
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
