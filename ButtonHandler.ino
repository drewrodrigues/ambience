#define SOLID_BUTTON_PIN 5
#define GRADIENT_BUTTON_PIN 6
#define PROGRAM_BUTTON_PIN 7

unsigned long lastButtonPressTime = millis();
unsigned long debounceDurationMs = 100;
// To require button to come up before continuing processing
ButtonType needButtonRelease = ButtonType::None;

// ? we can create a class or a struct instead? This can be much easier

int buttons[3] = {ButtonType::Solid, ButtonType::Gradient, ButtonType::Program};

void buttonHandlerSetup()
{
  pinMode(SOLID_BUTTON_PIN, INPUT);
  pinMode(GRADIENT_BUTTON_PIN, INPUT);
  pinMode(PROGRAM_BUTTON_PIN, INPUT);
}

ButtonType getButtonState()
{
  unsigned long timeNow = millis();
  bool debouncePassed = timeNow - lastButtonPressTime >= debounceDurationMs;

  Serial.println();
  Serial.println();

  Serial.println("getButtonState");
  Serial.print("timeNow: ");
  Serial.println(timeNow);

  Serial.print("debouncePassed: ");
  Serial.println(debouncePassed);

  Serial.print("lastButtonPressTime: ");
  Serial.println(lastButtonPressTime);

  Serial.print("needButtonRelease: ");
  Serial.println(needButtonRelease);

  Serial.println();
  Serial.println();

  if (!debouncePassed)
  {
    Serial.println("debouncing...");
    // need to wait longer until processing further / reading
    return ButtonType::None;
  }

  if (needButtonRelease != ButtonType::None)
  {
    if (readButtonFromType(needButtonRelease) == LOW)
    {
      Serial.println("...button released");
      needButtonRelease = ButtonType::None;
      // return ButtonType::None;
    }
    else
    {
      Serial.println("waiting for button release...");
      // Need to wait for button release. Otherwise,
      // we won't allow anything.
      return ButtonType::None;
    }
  }

  for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
  {
    if (readButtonFromType(buttons[i]) == HIGH)
    {
      Serial.print("Found a high button: ");
      Serial.println(buttons[i]);
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
  else if (buttonType == ButtonType::Program)
  {
    return digitalRead(PROGRAM_BUTTON_PIN);
  }
  else
  {
    return 0;
  }
}