CRGB getCycledRGB(unsigned int index)
{
  uint8_t phase = index % 768; // 256 per color transition

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