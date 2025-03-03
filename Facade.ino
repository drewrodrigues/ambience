#include <FastLED.h>

#include "Types.h"

/*
  Product: Ambience
  MC: ATTiny85
  LED: WS2812B-B/U (has internal decoupling capacitor)
  3 Buttons: Solid | Gradient | Dimmer
  Date: 8/25/2024
  Author: Drew Rodrigues

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
    - When swapping between solid/gradient, selection index resets for users
      to maintain sequential understanding over color order. This will help them
      find their favorite colors again quickly.
*/

#define LED_TYPE WS2812
#define LED_PIN 0
#define NUM_LEDS 24

CRGB leds[NUM_LEDS];

void setup()
{
  Serial.begin(9600);
  buttonHandlerSetup();

  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  FastLED.clear();
  nextSolid(leds);
}

void loop()
{
  static byte lastSelectedButton = ButtonType::None;

  ButtonType buttonState = getButtonState();
  if (buttonState == ButtonType::Solid)
  {
    lastSelectedButton = buttonState;
    nextSolid(leds);
  }
  else if (buttonState == ButtonType::Gradient)
  {
    lastSelectedButton = buttonState;
    nextAnimation(leds);
  }
  else if (buttonState == ButtonType::Dimmer)
  {
    digitalWrite(4, !digitalRead(4)); // TODO: @drew -- wtf is this?
    nextBrightness();
  }
  else if (lastSelectedButton == ButtonType::Gradient)
  {
    animate(leds);
  }
}