############### The Battery Builder ###############

This project allows the user to design a custom-made batterypack in an arbitrary series count and parallel count.

Series: Increases the maximum voltage output.
Parallel: Increases the maximum capacity.

###################################################

USAGE:
Best used in Visual Studio

In Terminal:
./driver <# Batteries in Series> <# Batteries in parallel>

Both must be > 0 and series must be an even number.


Visualize your battery:
./battery.html
use W, A, S, and D to move around.

###################################################

NOTE:
The default battery used is the P42A. This can be manually changed in batterypack.cpp (154).

Potential plans:
Add other battery options other than the P42A and allow for easier picking between battery types.

###################################################

Credits: 
Matthew Latta | https://github.com/mlatta824,
Jonnie Muench | ,
Christopher Tralie | https://github.com/ctralie
