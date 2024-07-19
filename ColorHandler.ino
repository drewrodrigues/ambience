#include <FastLED.h>

#define LED_TYPE WS2812
#define LED_PIN 8
#define NUM_LEDS 22

CRGB leds[NUM_LEDS];

void colorHandlerSetup()
{
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  // FastLED.addLeds<LED_TYPE, LED_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  FastLED.clear();
}

// namespace Gradient
// {
//   int Purp[2] = {0x7100FF, 0xE100FF};
//   int Sunrise[2] = {0xEF4136, 0xFBB040};
//   int Sunrise_Two[2] = {0xFFEC00, 0xFF100A};
//   // int BlueGreen[2] = {0x00A1FF, 0x00FF8F};
//   int OrangePurple[2] = {0xE33C40, 0x9937C8};
//   int Green[2] = {0x009124, 0x01FF3E};
//   // ❤️ TequilaSunrise: [0-6], [7, 17], [18, 21]
//   int TequilaSunrise[3] = {0xFFEC00, 0xFF100A, 0x600169};
//   /*
//     Some colors are overwhelming so we have to change the start and end
//     so colors don't get washed out.

//     Color: <hex>
//     Start: <integer>
//     EndInclusive: <integer>
//   */
//   // [0-13], [13-22]
//   int ClearSky[2] = {0x06EFFC, 0x071184};
// };

CRGB colors[] = {
    CRGB::Amethyst, // No
    CRGB::Black,    // Off
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
    nextProgram();
  }
}

int currentColor = 0;
const int COLOR_COUNT = sizeof(colors) / sizeof(colors[0]);
void nextSolid()
{
  currentColor = (currentColor + 1) % COLOR_COUNT;

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = colors[currentColor];
    // leds[i] = Gradient::Purp::Begin;
  }
  FastLED.show();
}

void nextGradient()
{
  // for (int i = 7; i < 18; i++) {
  //   leds[i] = Gradient::TequilaSunrise[1];
  //   // leds[i] = CRGB::Green;
  // }
  // for (int i = 18; i < 22; i++) {
  // leds[i] = CRGB::Yellow;
  //   // leds[i] = Gradient::Purp::End;
  //   leds[i] = Gradient::TequilaSunrise[2];
  // }

  // for (int i = (0 + step) % 22; i < (0 + step) % 22; i++) {
  //   leds[i] = Gradient::Green[0];
  //   // leds[i] = Gradient::Purp::Begin;
  // }
  // for (int i = (14 + step) % 22; i < (14 + step) % 22; i++) {
  //   leds[i] = Gradient::Green[1];
  // }
  // for (int i = (18 + step) % 22; i < (22 + step) % 22; i++) {
  //   leds[i] = Gradient::TequilaSunrise[2];
  // }
}

void nextProgram()
{
}