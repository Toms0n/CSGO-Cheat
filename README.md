# CSGO-Cheat

## Performance TODOS:  
1. Check if usage of `std::shared_ptr` has effect on performance. If so then instantiate classes using pointers with `delete` to discard them manually.  
2. Decrease amount of `WPM` and `RPM` calls where possible to make code more efficient.  
3. Initialize private data of classes in the public constructor (to e.g. nullptr or 0) in classes the dont do that.
4. Initialization of `CsgoCheats` can be done better maybe?  

## General TODOS:
1. Make the cheats in main functions (e.g. aimbot, glow etc...) toggelable instead of exiting the cheat.  
2. Prevent using `64` as in the loops and store only enemies in a `std::vector` for example and loop through it. Also check whether max players can be fetched from memory.  
2. **IMPORTANT TODO:** Aimbot sometimes flicks to enemy without me pressing the left button of the mouse. Uncommenting isSpotted() check in aimbot fixes this, but slows down the aimbot AFAIK.  
3. Remove unnecessary code from e.g. Maths.h (as many implementation are not needed for external cheat).  
4. Make glow depending on health of enemy (going from green color to yellow to red upon damaging the enemy).  
5. Make all functions in `CsgoCheats` class `const`. So like this `DWORD getPlayer(...) *const*`.