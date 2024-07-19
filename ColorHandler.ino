#include <FastLED.h>

#define LED_TYPE WS2812
#define LED_PIN 8
#define NUM_LEDS 22

CRGB leds[NUM_LEDS];

void colorHandlerSetup()
{
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);
  FastLED.clear();
}

// TODO: enable more than 2?
HexRange gradients[][2] = {
    {HexRange(0x7100FF, 0, 10), HexRange(0xFBB040, 10, NUM_LEDS)},
    {HexRange(0xEF4136, 0, 10), HexRange(0xFBB040, 10, NUM_LEDS)},
    {HexRange(0xE33C40, 0, 10), HexRange(0x9937C8, 10, NUM_LEDS)},    // orange purple
    {HexRange(0xFFEC00, 0, 10), HexRange(0xFF100A, 10, NUM_LEDS)},    // part of tequila sunrise
    {HexRange(0x06EFFC, 0, 10), HexRange(0x071184, 10, NUM_LEDS)},    // clear sky
    {HexRange(CRGB::Red, 0, 10), HexRange(CRGB::Blue, 10, NUM_LEDS)}, // red -> blue
    {HexRange(0x009124, 0, 10), HexRange(0x01FF3E, 10, NUM_LEDS)}};   // green

CRGB colors[] = {
    CRGB::Amethyst, // No
    // CRGB::Black,    // Off
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

unsigned int solidColor = 0;
const unsigned int COLOR_COUNT = sizeof(colors) / sizeof(colors[0]);
void nextSolid()
{
  solidColor = (solidColor + 1) % COLOR_COUNT;

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = colors[solidColor];
  }

  FastLED.show();
}

unsigned int gradientColor = 0;
const unsigned int GRADIENT_COUNT = sizeof(gradients) / sizeof(gradients[0]);
void nextGradient()
{
  gradientColor = (gradientColor + 1) % GRADIENT_COUNT;

  HexRange currentGradient[2] = gradients[gradientColor];

  for (int i = 0; i < 2; i++)
  {
    HexRange hexRange = currentGradient[i];

    // * if we write out of the range, we end up overwriting other memory that's not ours
    if (hexRange.endRange > NUM_LEDS)
    {
      Serial.println("[ERROR]: Hex range upper exclusive ending range is out of range of LEDs.");
      return;
    }

    for (int j = hexRange.startRange; j < hexRange.endRange; j++)
    {
      leds[j] = hexRange.hexValue;
    }
  }

  FastLED.show();
}

unsigned int selectedProgramIdx = 0;
void nextProgram()
{
  // none

  CRGB previousColors[NUM_LEDS] = {};
  // turn one at a time in a circle
  for (int i = 0; i < NUM_LEDS; i++)
  {
    previousColors[i] = leds[i];
    leds[i] = CRGB::Black;
  }

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = previousColors[i];
    FastLED.show();
    FastLED.delay(100);
    leds[i] = CRGB::Black;
  }
  // turn on every other one and then push it forward
}

void onNextColor(ButtonType buttonType)
{
  if (buttonType == ButtonType::Solid)
  {
    nextSolid();
  }
  else if (buttonType == ButtonType::Gradient)
  {
    nextGradient();
  }
  else if (buttonType == ButtonType::Program)
  {
    Serial.println("Program button clicked");
    nextProgram();
  }
}