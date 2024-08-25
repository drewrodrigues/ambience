# Gotchas

- Be careful when loading large variables into memory at runtime. It can cause a stack/heap? overflow which can crash the program. Instead, use `PROGMEM` for large variables / lookup tables.
- Writing to `Serial` can cause problem on certain pins. Remove all login and serial communication setup before trying debugging other methods. Otherwise, this can cause a huge time sink.

# Memory

- Flash: Persistant (stores executable sketch, limited writes ~10,000)
- RAM/SRAM: Variables, stack, etc
- EEPROM: Persistance storage (limited writes ~10,000)
  - Be careful writing to this too often, as it can eventually fail
