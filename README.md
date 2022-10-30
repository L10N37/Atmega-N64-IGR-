# Atmega-N64-IGR-
N64 In game reset using 168P / 328P Atmega MCU
#IGR COMBO: L+R+A+B+Z


Needs to run off 5v as 3.3v won't cut it for some reason.
Nothing is ever sent across as a logic 5v high through the controller ports serial line, it just floats about and sniffs the inputs.

It's a hacked up version of John Crain Welsby/ LogicalUnits N64 Interface. (https://github.com/LogicalUnit/N64_Interface)
Though, i found my issue when attempting to start my own was using microseconds delays where he used NOPS. They must not be accurate.
No point re-inventing the wheel though, this was here so it's being modified to suit! 

There are 2 places to grab the serial controller from dependant on the N64 revision. Either directly off the PIF chip leg or a via nearby.
The reset pin does not differ though.
Alternatively, you could grab the points off under the board for reset and the controllers centre pin is the serial transmission captured.

For power, 5v regulator output, for ground the space on the rear of the 5v regulator (where it mounts to sit flush) is good. 
