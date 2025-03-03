#include <FastLED.h>

byte selectedAnimation = 0;
uint8_t hue = 0;
uint8_t pos = 0;
uint8_t sparkleIndex = 0;

void nextAnimation(CRGB* leds)
{
    const byte ANIMATION_COUNT = 10;
    selectedAnimation = (selectedAnimation + 1) % ANIMATION_COUNT;
    animate(leds);
    FastLED.show();
}

void animate(CRGB* leds)
{
    static unsigned long lastUpdate = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - lastUpdate >= 50)
    {
        lastUpdate = currentMillis;

        switch (selectedAnimation)
        {
        case 0:
            rainbowCycle(leds);
            break;
        case 1:
            chasingEffect(leds);
            break;
        case 2:
            pulsingEffect(leds);
            break;
        case 3:
            fireEffect(leds);
            break;
        case 4:
            sparkleEffect(leds);
            break;
        case 5:
            bouncingBallEffect(leds);
            break;
        case 6:
            waveEffect(leds);
            break;
        case 7:
            scannerEffect(leds);
            break;
        case 8:
            flickerEffect(leds);
            break;
        case 9:
            rgbCycleEffect(leds);
            break;
        }
        FastLED.show();
    }
}

void rainbowCycle(CRGB* leds)
{
    hue++;
    fill_rainbow(leds, NUM_LEDS, hue);
}

void chasingEffect(CRGB* leds)
{
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    leds[pos] = CRGB::White;
    pos = (pos + 1) % NUM_LEDS;
}

void pulsingEffect(CRGB* leds)
{
    uint8_t brightness = sin8(millis() / 10);
    fill_solid(leds, NUM_LEDS, CHSV(hue, 255, brightness));
}

void fireEffect(CRGB* leds)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = HeatColor(random8(100, 255));
    }
}

void sparkleEffect(CRGB* leds)
{
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    leds[random8(NUM_LEDS)] = CRGB::White;
}

void bouncingBallEffect(CRGB* leds)
{
    static int ballPos = 0;
    static int direction = 1;
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    leds[ballPos] = CRGB::White;

    ballPos += direction;
    if (ballPos == 0 || ballPos == NUM_LEDS - 1)
    {
        direction *= -1;
    }
}

void waveEffect(CRGB* leds)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = CHSV((hue + i * 15) % 255, 255, 255);
    }
    hue += 2;
}

void scannerEffect(CRGB* leds)
{
    static int pos = 0;
    static int direction = 1;
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    leds[pos] = CRGB::White;

    pos += direction;
    if (pos == 0 || pos == NUM_LEDS - 1)
    {
        direction *= -1;
    }
}

void flickerEffect(CRGB* leds)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = CRGB(random8(180, 255), random8(100, 150), random8(0, 50));
    }
}

void rgbCycleEffect(CRGB* leds)
{
    static int colorIndex = 0;

    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = CHSV((colorIndex + i * 10) % 255, 255, 255);
    }
    colorIndex++;
}