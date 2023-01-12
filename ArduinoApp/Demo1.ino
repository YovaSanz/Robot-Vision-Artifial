#include <avr/wdt.h>
#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.cpp"

DeviceDriverSet_Motor AppMotor;
Application_xxx Application_ConquerorCarxxx0;

int dire = 8;
int vel = 0;

void setup() {
  Serial.begin(9600);

  AppMotor.DeviceDriverSet_Motor_Init();
  delay(2000);

}

void loop() {
   
  speed(dire, 70);

}

// Funcion que se activa al recibir algo por
// el puerto serie, Interrupcion del puerto Serie.
void serialEvent(){

  if(Serial.available()){
    char data = Serial.read();

    if(data >= '0' && data <= '9'){
      data -= '0';
      //Serial.println((int)data);

      dire = data;
    }    

  }

}

void speed(int direccion, int velocidad){

  Application_ConquerorCarxxx0.Motion_Control = direccion;
  ApplicationFunctionSet_ConquerorCarMotionControl(Application_ConquerorCarxxx0.Motion_Control /*direction*/, velocidad /*speed*/);
  
}

