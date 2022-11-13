# Atmega-N64-IGR-
N64 In game reset using 168P / 328P Atmega MCU
## IGR COMBO: L+R+A+B+Z


Needs to run off 5v as 3.3v won't cut it for some reason.
Nothing is ever sent across as a logic 5v high through the controller ports serial line, it just floats about and sniffs the inputs.

It's a hacked up version of John Crain Welsby/ LogicalUnits N64 Interface. (https://github.com/LogicalUnit/N64_Interface)
Though, i found my issue when attempting to start my own was using microseconds delays where he used NOPS. They must not be accurate.
No point re-inventing the wheel though, this was here so it's being modified to suit! 

##  4 wires 

  - 5v to VIN
  - Gnd to a Ground point
  - D2 to controller serial data via 120r resistor
  - D4 to PIF reset pin
  
  You may want to experiment with the resistor value, it's there as a filter and prevents phantom button presses

There are 2 places to grab the serial stream from the controller dependant on the N64 revision. Either directly off the PIF chip leg or a via nearby.
You need to grab the right point for your board.

The reset pin does not differ though.
Alternatively, you could grab the points off under the board for reset and the controllers centre pin is the serial transmission captured. 

For power, 5v regulator output, for ground the space on the rear of the 5v regulator (where it mounts to sit flush) is good. 

And remember folks, those ED64 / ED64 PLUS won't save your games without resetting before a power off!
