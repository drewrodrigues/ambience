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

*/

void setup()
{
  Serial.begin(9600);
  colorHandlerSetup();
  buttonHandlerSetup();
}

void loop()
{
  ButtonType buttonState = getButtonState();
  if (buttonState != ButtonType::None)
  {
    onNextColor(buttonState);
  }
}