unsigned long lastButtonPressTime = millis();
unsigned long debounceDurationMs = 250;
// To require button to come up before continuing processing
ButtonType needButtonRelease = ButtonType::None;

const byte buttons[3] = {ButtonType::Solid, ButtonType::Gradient, ButtonType::Dimmer};

void buttonHandlerSetup()
{
  // INPUT_PULLUP is to avoid floating HIGH voltage
  // so, we invert. HIGH will be up and LOW will be pressed
  pinMode(ButtonType::Solid, INPUT_PULLUP);
  pinMode(ButtonType::Gradient, INPUT_PULLUP);
  pinMode(ButtonType::Dimmer, INPUT_PULLUP);
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
    if (digitalRead(needButtonRelease) == HIGH) // released
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

  for (byte i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
  {
    if (digitalRead(buttons[i]) == LOW) // pressed down
    {
      needButtonRelease = buttons[i];
      lastButtonPressTime = millis();
      return buttons[i];
    }
  }

  // Otherwise, we can have errors where it thinks a button was clicked
  return ButtonType::None;
}