#include <FastLED.h>
#include <avr/pgmspace.h>

void nextSolid(CRGB *leds)
{
  static unsigned int colorIndex = 0;
  ifOffTurnTofullBrightness();

  CRGB color = getCycledRGB(colorIndex);
  for (byte i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = color;
  }
  colorIndex += (768 / 40);

  FastLED.show();
}

bool goUp = false;
static byte selectedBrightness = 3;
void nextBrightness()
{

  const byte brightnesses[4] = {0, 50, 150, 255};
  const byte BRIGHTNESS_COUNT = sizeof(brightnesses) / sizeof(brightnesses[0]);
  const byte prevSelectedBrightness = selectedBrightness;

  if (goUp)
  {
    selectedBrightness++;
  }
  else
  {
    selectedBrightness--;
  }

  if (prevSelectedBrightness == 2 && goUp)
  {
    goUp = false;
  }
  else if (prevSelectedBrightness == 1 && !goUp)
  {
    goUp = true;
  }

  FastLED.setBrightness(brightnesses[selectedBrightness]);
  FastLED.show();
}

/*
  This is so it's not confusing if changing the color when the dimmer is off
*/
void ifOffTurnTofullBrightness()
{
  if (selectedBrightness == 0)
  {
    selectedBrightness = 3;
    goUp = false;
    FastLED.setBrightness(255);
    FastLED.show();
  }
}