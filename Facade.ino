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
  Serial.begin(9600);
  // colorHandlerSetup();
  buttonHandlerSetup();

  // ! manual testing button circuit on PCB
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop()
{
  // ! manual testing button circuit on PCB
  ButtonType buttonState = getButtonState();
  if (buttonState == ButtonType::Solid)
  {
    digitalWrite(3, HIGH);
  }
  else if (buttonState == ButtonType::Gradient)
  {
    digitalWrite(4, HIGH);
  }
  else if (buttonState == ButtonType::Dimmer)
  {
    digitalWrite(5, HIGH);
  }

  delay(500);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  // if (buttonState != ButtonType::None)
  // {
  //   onNextColor(buttonState);
  // }

  /*
  if (buttonState == ButtonType::Solid)
  {
    nextSolid();
  }
  else if (buttonState == ButtonType::Gradient)
  {
    nextGradient();
  }
  else if (buttonState == ButtonType::Dimmer)
  {
    nextBrightness();
  }
  else
  {
    // do nothing my guy
  }
  */
}