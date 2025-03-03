#include <FastLED.h>
#include <avr/pgmspace.h>

#define LED_TYPE WS2812
#define LED_PIN 0
#define NUM_LEDS 24

CRGB leds[NUM_LEDS];

void colorHandlerSetup()
{
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  FastLED.clear();
  nextSolid();
}

void nextSolid()
{
  static unsigned int colorIndex = 0;
  ifOffTurnTofullBrightness();

  for (byte i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = getCycledRGB(colorIndex);
  }
  colorIndex += (768 / 40);

  FastLED.show();
}

void nextGradient()
{
  ifOffTurnTofullBrightness();

  CRGB color1 = CRGB(random(256), random(256), random(256));
  CRGB color2 = CRGB(random(256), random(256), random(256));

  for (byte i = 0; i < NUM_LEDS; i++)
  {
    float ratio = (float)i / (NUM_LEDS - 1);
    leds[i] = blend(color1, color2, ratio * 255);
  }

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

CRGB getCycledRGB(int index)
{
  int phase = index % 768; // 256 per color transition

  if (phase < 256)
  {
    return CRGB(255 - phase, phase, 0); // Red -> Green
  }
  else if (phase < 512)
  {
    return CRGB(0, 255 - (phase - 256), phase - 256); // Green -> Blue
  }
  else
  {
    return CRGB(phase - 512, 0, 255 - (phase - 512)); // Blue -> Red
  }
}