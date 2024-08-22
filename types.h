enum ButtonType
{
  Solid = 1,
  Gradient = 2,
  Dimmer = 3,
  None = 4
};
struct HexRange
{
  uint32_t hexValue;
  int startRange;
  int endRange;
  HexRange(uint32_t hex, int start, int end) : hexValue(hex), startRange(start), endRange(end) {}
};