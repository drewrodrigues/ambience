#include "Types.h"

/*
  MC: ATMega328P-PU
  LED: WS2812 (what density?)
  3 Buttons: Solid | Gradient | Program
*/

/*

Handle state changes once, instead of continually doing the same thing
currentState != previousState
  - do changes


When gradient button is hit, it looks like the MC is resetting...
*/

void setup()
{
  Serial.begin(9600);
  Serial.println("Facade 1.0");
  colorHandlerSetup();
  buttonHandlerSetup();
}

void loop()
{
  ButtonType buttonState = getButtonState();
  onNextColor(buttonState);
}