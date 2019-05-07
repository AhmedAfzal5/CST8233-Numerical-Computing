# Bungee Jump

## Purpose
While the user wishes to continue, the application will ask the user to select whether to run
the simulation one more time. The simulation uses Heun’s method, as explained in lectures, to solve a
differential equation for acceleration under gravity, with controllable wind drag and with an additional
elastic restoring term B so as to simulate falling off the top of a 200 metres high tower with a 10 metre
length bungee cord tied to your ankles. The task is to reach the ground (height < 1.0 metres) at low speed
(<1.0 metres/sec) so you can safely slip off the bungee and walk away. With no wind drag you’ll probably
hit the ground faster than 1metre/sec and die, but with too much drag you will not reach the ground al all
but instead oscillate until you come to rest suspended 25m above the ground. Wind drag is adjustable
from the keyboard ‘w’ increases it, ‘e’ decreases it. You can use _kbhit() to detect a key press and then
_getch() to discover which key.
There is a “bare-bones” console executable, bungee.exe, on BB that that runs the simulation as a single
shot – it does not offer a repeat. Your version should work the same, displaying the same information, but
allow repeat

## Screenshots of Program
