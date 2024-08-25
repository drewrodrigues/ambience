#include "Types.h"

/*
  MC: ATMega328P-PU
  LED: WS2812B-B/U (has internal decoupling capacitor)
  3 Buttons: Solid | Gradient | Dimmer
*/

void setup()
{
  colorHandlerSetup();
  buttonHandlerSetup();
}

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