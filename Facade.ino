#include "Types.h"

/*

Debugging steps:
- Hook up buttons
- When a button is pressed, trigger a LED output (to see if any are being held down?)
*/

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
  colorHandlerSetup(); // ! only difference
  buttonHandlerSetup();
  pinMode(4, OUTPUT); // just for testing buttons manually
}

// PIN 4 is OUTPUT LED

byte lastSelectedButton = ButtonType::None;
void loop()
{
  ButtonType buttonState = getButtonState();
  if (buttonState == ButtonType::Solid)
  {
    if (lastSelectedButton == ButtonType::Gradient)
    {
      resetSolidIndex();
    }
    lastSelectedButton = buttonState;
    nextSolid();
  }
  else if (buttonState == ButtonType::Gradient)
  {
    if (lastSelectedButton == ButtonType::Solid)
    {
      resetGradientIndex();
    }
    lastSelectedButton = buttonState;
    nextGradient();
  }
  else if (buttonState == ButtonType::Dimmer)
  {
    digitalWrite(4, !digitalRead(4));
    nextBrightness();
  }
}