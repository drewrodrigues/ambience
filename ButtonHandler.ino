unsigned long lastButtonPressTime = millis();
unsigned long debounceDurationMs = 250;
// To require button to come up before continuing processing
ButtonType heldDownButton = ButtonType::None;

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
    return ButtonType::None;
  }

  /*
    Keep track of button up/down state so we can allow button clicks on holding
    down a button. But not allow other buttons to register while that button
    is being held down. Once it's released, it's free game.
  */
  if (heldDownButton != ButtonType::None)
  {
    const bool buttonIsReleased = digitalRead(heldDownButton) == HIGH;
    if (buttonIsReleased)
    {
      heldDownButton = ButtonType::None;
    }
  }

  for (byte i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
  {
    // we'll allow further clicks from a held down button, but not allow
    // other held down buttons to register until the initial one is released
    if (heldDownButton != ButtonType::None && heldDownButton != buttons[i])
      continue;

    const bool buttonIsPressed = digitalRead(buttons[i]) == LOW;
    if (buttonIsPressed)
    {
      heldDownButton = buttons[i];
      lastButtonPressTime = millis();
      return buttons[i];
    }
  }

  // Otherwise, we can have errors where it thinks a button was clicked
  return ButtonType::None;
}