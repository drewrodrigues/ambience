#include "Types.h"

/*
  MC: ATMega328P-PU
  LED: WS2812B-B/U (has internal decoupling capacitor)
  3 Buttons: Solid | Gradient | Dimmer

  Features:
    - Held down buttons continue triggering after debouce duration
    - When a button is held down, it must be released before other buttons are
      registered
    - 3 buttons handled: Solid, Gradient, Dimmer
    - Solid color selection
    - Gradient color selection
    - Dimmer selection (up/down) for smoother experience
    - Input pullup on buttons to remove pulldown resistors in circuit
    - Solid colors and gradients written/pulled from memory to reduce ram usage
    - When selecting solid/gradient when dimmer has turned off LEDs, light goes
      back to full brightness for understandability.
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