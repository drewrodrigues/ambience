#include <FastLED.h>

#define LED_TYPE WS2812
#define LED_PIN 0
#define NUM_LEDS 10

CRGB leds[NUM_LEDS];

void colorHandlerSetup()
{
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);
  FastLED.clear();
}

const CRGB colors[] PROGMEM = {
    CRGB::Amethyst, // No
    CRGB::Aqua,
    CRGB::Blue,
    CRGB::BlueViolet,
    CRGB::Brown,      // ? Yes, but this is more salmon
    CRGB::Chartreuse, // Lawn green
    CRGB::Crimson,    // Deep pink, super cool!
    CRGB::Cyan,       // ❤️
    CRGB::DarkBlue,
    CRGB::DarkCyan,
    CRGB::DarkGoldenrod, // Not sure...
    CRGB::DarkGreen,
    CRGB::DarkMagenta,
    CRGB::DarkOrange,
    CRGB::DarkOrchid,
    CRGB::DarkRed,
    CRGB::DarkSlateGray,
    CRGB::DarkTurquoise,
    CRGB::DarkViolet,
    CRGB::DeepPink,
    CRGB::DeepSkyBlue,
    CRGB::DodgerBlue,
    CRGB::FireBrick,
    CRGB::ForestGreen,
    CRGB::Fuchsia,
    CRGB::GhostWhite,
    CRGB::Gold,
    CRGB::Grey,
    CRGB::Green,
    CRGB::HotPink,
    CRGB::IndianRed,
    CRGB::Indigo,
    CRGB::LawnGreen,
    CRGB::LightSeaGreen,
    CRGB::LightSkyBlue,
    CRGB::Lime,
    CRGB::Magenta,
    CRGB::Maroon,
    CRGB::MediumBlue,
    CRGB::MediumOrchid,
    CRGB::MediumSpringGreen,
    CRGB::MediumVioletRed,
    CRGB::MidnightBlue,
    CRGB::Navy,
    CRGB::Olive,
    CRGB::Orange,
    CRGB::OrangeRed,
    CRGB::Pink, // Maybe
    CRGB::PowderBlue,
    CRGB::Purple,
    CRGB::Red,
    CRGB::Sienna,
    CRGB::SlateBlue,
    CRGB::SpringGreen,
    CRGB::SteelBlue,
    CRGB::Teal,
    CRGB::White,
    CRGB::Yellow,
    // LED RGB color that roughly approximates
    // the color of incandescent fairy lights,
    // assuming that you're using FastLED
    // color correction on your LEDs (recommended).
    CRGB::FairyLight};

byte solidColor = 0;
void nextSolid()
{
  const byte COLOR_COUNT = sizeof(colors) / sizeof(colors[0]);
  solidColor = (solidColor + 1) % COLOR_COUNT;

  for (byte i = 0; i < NUM_LEDS; i++)
  {
    CRGB color;
    memcpy_P(&color, &colors[solidColor], sizeof(CRGB));
    leds[i] = color;
  }

  FastLED.show();
}

const HexRange gradients[][2] = {
    {HexRange(0x7100FF, 0, 5), HexRange(0xFBB040, 5, NUM_LEDS)},
    {HexRange(0xEF4136, 0, 5), HexRange(0xFBB040, 5, NUM_LEDS)},
    {HexRange(0xE33C40, 0, 5), HexRange(0x9937C8, 5, NUM_LEDS)},    // orange purple
    {HexRange(0xFFEC00, 0, 5), HexRange(0xFF100A, 5, NUM_LEDS)},    // part of tequila sunrise
    {HexRange(0x06EFFC, 0, 5), HexRange(0x071184, 5, NUM_LEDS)},    // clear sky
    {HexRange(CRGB::Red, 0, 5), HexRange(CRGB::Blue, 5, NUM_LEDS)}, // red -> blue
    {HexRange(0x009124, 0, 5), HexRange(0x01FF3E, 5, NUM_LEDS)}};   // green
int gradientColor = 0;
void nextGradient()
{
  const int GRADIENT_COUNT = sizeof(gradients) / sizeof(gradients[0]);
  gradientColor = (gradientColor + 1) % GRADIENT_COUNT;

  for (int i = 0; i < 2; i++)
  {
    HexRange hexRange = gradients[gradientColor][i];

    // * if we write out of the range, we end up overwriting other memory that's not ours
    // ! this caused a lot of issues -- it causes everything to lock up (probably nto allowing the counter to increment?)
    if (hexRange.endRange > NUM_LEDS || hexRange.startRange > NUM_LEDS || hexRange.startRange > hexRange.endRange)
    {
      break;
    }

    for (int j = hexRange.startRange; j < hexRange.endRange; j++)
    {
      leds[j] = hexRange.hexValue;
    }
  }

  FastLED.show();
}

unsigned short int selectedBrightness = 0;
void nextBrightness()
{
  unsigned short int brightnesses[6] = {0, 50, 100, 150, 200, 255};
  const unsigned int BRIGHTNESS_COUNT = sizeof(brightnesses) / sizeof(brightnesses[0]);

  selectedBrightness = (selectedBrightness + 1) % BRIGHTNESS_COUNT;
  FastLED.setBrightness(brightnesses[selectedBrightness]);
}