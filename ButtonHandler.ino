#define SOLID_BUTTON_PIN 5
#define GRADIENT_BUTTON_PIN 6
#define PROGRAM_BUTTON_PIN 7

unsigned long lastButtonPress = millis();
unsigned long debounceDurationMs = 100;
unsigned long currentTime = millis();

void buttonHandlerSetup()
{
  pinMode(SOLID_BUTTON_PIN, INPUT);
  pinMode(GRADIENT_BUTTON_PIN, INPUT);
  pinMode(PROGRAM_BUTTON_PIN, INPUT);
}

ButtonType getButtonState()
{
  // currentTime = millis();
  // bool debouncePassed = lastButtonPress + debounceDurationMs > currentTime;
  // if (!debouncePassed)
  // {
  //   // need to wait longer until processing further / reading
  //   return ButtonType::None;
  // }

  // bool solidButtonState = digitalRead(SOLID_BUTTON_PIN);
  // if (solidButtonState == HIGH)
  // {
  //   return ButtonType::Solid;
  // }

  // bool gradientButtonState = digitalRead(GRADIENT_BUTTON_PIN);
  // if (gradientButtonState == HIGH)
  // {
  //   return ButtonType::Gradient;
  // }

  // bool programButtonState = digitalRead(PROGRAM_BUTTON_PIN);
  // if (programButtonState == HIGH)
  // {
  //   return ButtonType::Program
  // }
}