enum ButtonType
{
  Solid = 0,
  Gradient = 1,
  Dimmer = 2,
  None = 3
};
struct HexRange
{
  uint32_t hexValue;
  int startRange;
  int endRange;
  HexRange(uint32_t hex, int start, int end) : hexValue(hex), startRange(start), endRange(end) {}
};