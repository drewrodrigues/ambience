#include "types.h"

/*
  MC: ATMega328
  LED: WS2812
  3 Buttons: Solid | Gradient | Program
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