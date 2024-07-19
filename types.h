enum ButtonType
{
  Solid,
  Gradient,
  Program,
  None
};
struct HexRange
{
  uint32_t hexValue;
  int startRange;
  int endRange;
  HexRange(uint32_t hex, int start, int end) : hexValue(hex), startRange(start), endRange(end) {}
};