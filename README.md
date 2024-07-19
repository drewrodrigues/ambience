# Reasoning

Arduino IDE is erroring out on a signature error: `avrdude: device signature = 0x1e950f (probably m328p)`. So, we must force each of the commands manually since we know we're selecting the correct MC.

# Hardware

## Specs

- 5V DC power supply

![](/ATMega328Pinout.png)

## Burn Bootloader on ATMega328P-U

### Setup Arduino Embedded MC

1. `Files > Examples > 11.ArduinoISP > ArduinoESP`
2. Upload to Arduino Uno (with bootloader circuit disconnected)

### Setup Circuit

1. Connect bootloader circuit with external ATMega328P-U connected

   - Ensure there's a 10nanoF capacitor with negative leg in ground and positive in reset on Arduion.
   - Ensure the original ATMega328P-U is on the Arduino Uno board and has the `Arduino as ISP` example has been uploaded to it first.

- ![](/IMG_2707.jpg)
- ![](/IMG_2708.jpg)
- ![](/IMG_2709.jpg)

### Burn Bootloader onto External MC

**Note: The `MiniCore` library must be installed first**
**Note: Ensure debugging mode is on Arduino IDE, so script commands can be copied.**

1. Select the following settings:
   ![](/settings.png)

Run: `"/Users/drew/Library/Arduino15/packages/MiniCore/tools/avrdude/7.2-arduino.1/bin/avrdude" "-C/Users/drew/Library/Arduino15/packages/MiniCore/hardware/avr/3.0.2/avrdude.conf" -v -patmega328 -cstk500v1 -P/dev/cu.usbmodem212101 -b19200 -e -Ulock:w:0xff:m -Uefuse:w:0b11111101:m -Uhfuse:w:0xd7:m -Ulfuse:w:0xe2:m -F`

## Upload Code to ATMega328P-U

1. Open the sketch you want to upload
2. `Sketch -> Upload Using Programming`

3. This will fail. So copy the command and append `-F` to the end. It will look something like: `"/Users/drew/Library/Arduino15/packages/MiniCore/tools/avrdude/7.2-arduino.1/bin/avrdude" "-C/Users/drew/Library/Arduino15/packages/MiniCore/hardware/avr/3.0.2/avrdude.conf" -v -V -patmega328 -cstk500v1 -P/dev/cu.usbmodem212101 -b19200 "-Ueeprom:w:/private/var/folders/1v/6223zx0x1wq5d2rh31yd8n1r0000gn/T/arduino/sketches/B3DFF97B33CA8B957F9F4892374529CF/sketch_jul17b.ino.eep:i" "-Uflash:w:/private/var/folders/1v/6223zx0x1wq5d2rh31yd8n1r0000gn/T/arduino/sketches/B3DFF97B33CA8B957F9F4892374529CF/sketch_jul17b.ino.hex:i" -F`
