#include "LedControl.h"

LedControl lc=LedControl(11,13,10,4);  // DIN,CLK,CS,Number of LED Module

unsigned long delaytime=10;  // time to updates of the display

void setup() {
  int devices=lc.getDeviceCount();  // find no of LED modules
  //we have to init all devices in a loop
  for(int address=0;address<devices;address++) {  // set up each device 
    lc.shutdown(address,false);
    lc.setIntensity(address,8);
    lc.clearDisplay(address);
  }
}

void loop() { 
  int devices=lc.getDeviceCount();  // find no of LED modules

  for (int row = 0; row < 8; row++) {
    for(int address=0;address<devices;address++) {
          delay(delaytime);
          lc.setLed(address,row,0,true);
          delay(delaytime);
          lc.setLed(address,row,0,false);
      }
  }

  for (int col = 1; col < 8; col++) {
    for(int address=0;address<devices;address++) {
          delay(delaytime);
          lc.setLed(address,7,col,true);
          delay(delaytime);
          lc.setLed(address,7,col,false);
      }
  }

  for (int row = 6; row >= 0; row--) {
    for(int address=0;address<devices;address++) {
          delay(delaytime);
          lc.setLed(address,row,7,true);
          delay(delaytime);
          lc.setLed(address,row,7,false);
      }
  }

  for (int col = 6; col > 0; col--) {
    for(int address=0;address<devices;address++) {
          delay(delaytime);
          lc.setLed(address,0,col,true);
          delay(delaytime);
          lc.setLed(address,0,col,false);
      }
  }
}
