#define SOLID_BUTTON_PIN 5
#define GRADIENT_BUTTON_PIN 6
#define PROGRAM_BUTTON_PIN 7

unsigned long lastButtonPress = millis();
unsigned long debounceDurationMs = 100;
// To require button to come up before continuing processing
ButtonType needButtonRelease = ButtonType::None;

// ? we can create a class or a struct instead? This can be much easier

// int buttons[3] = {ButtonType::Solid, ButtonType::Gradient, ButtonType::Program};
int buttons[1] = {ButtonType::Solid};

void buttonHandlerSetup()
{
  pinMode(SOLID_BUTTON_PIN, INPUT);
  pinMode(GRADIENT_BUTTON_PIN, INPUT);
  pinMode(PROGRAM_BUTTON_PIN, INPUT);
}

ButtonType getButtonState()
{
  bool debouncePassed = millis() - lastButtonPress >= debounceDurationMs;
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
      Serial.println("In it");
      needButtonRelease = buttons[i];
      lastButtonPress = millis();
      return buttons[i];
    }
  }
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
  else if (buttonType == ButtonType::Program)
  {
    return digitalRead(PROGRAM_BUTTON_PIN);
  }
  else
  {
    return 0;
  }
}