#define SOLID_BUTTON_PIN 0
#define GRADIENT_BUTTON_PIN 1
#define DIMMER_BUTTON_PIN 2

unsigned long lastButtonPressTime = millis();
unsigned long debounceDurationMs = 100;
// To require button to come up before continuing processing
ButtonType needButtonRelease = ButtonType::None;

// ? we can create a class or a struct instead? This can be much easier

int buttons[3] = {ButtonType::Solid, ButtonType::Gradient, ButtonType::Dimmer};

void buttonHandlerSetup()
{
  pinMode(SOLID_BUTTON_PIN, INPUT);
  pinMode(GRADIENT_BUTTON_PIN, INPUT);
  pinMode(DIMMER_BUTTON_PIN, INPUT);
}

ButtonType getButtonState()
{
  unsigned long timeNow = millis();
  bool debouncePassed = timeNow - lastButtonPressTime >= debounceDurationMs;

  if (!debouncePassed)
  {
    // need to wait longer until processing further / reading
    return ButtonType::None;
  }

  if (needButtonRelease != ButtonType::None)
  {
    if (readButtonFromType(needButtonRelease) == LOW)
    {
      needButtonRelease = ButtonType::None;
      // return ButtonType::None;
    }
    else
    {
      // Need to wait for button release. Otherwise,
      // we won't allow anything.
      return ButtonType::None;
    }
  }

  for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
  {
    if (readButtonFromType(buttons[i]) == HIGH)
    {
      needButtonRelease = buttons[i];
      lastButtonPressTime = millis();
      return buttons[i];
    }
  }

  // Otherwise, we can have errors where it thinks a button was clicked
  return ButtonType::None;
}

int readButtonFromType(ButtonType buttonType)
{
  if (buttonType == ButtonType::Solid)
  {
    return digitalRead(SOLID_BUTTON_PIN);
  }
  else if (buttonType == ButtonType::Gradient)
  {
    return digitalRead(GRADIENT_BUTTON_PIN);
  }
  else if (buttonType == ButtonType::Dimmer)
  {
    return digitalRead(DIMMER_BUTTON_PIN);
  }
  else
  {
    return 0;
  }
}