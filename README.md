# xinput2600
XInput Adapter for Atari 2600 Controllers

This project was initially created for [Starlords](https://www.tested.com/premium/852029-bits-atoms-starlords-arcade-cabinet-part-1/), 
a physical arcade game & cabinet developed by Tested.com and Other Ocean Interactive. This code, when paried with 
[the PCB available on OshPark](https://oshpark.com/shared_projects/ybyjPbuy), converts signals from original Atari 2600 controllers 
to XInput, combining either two Joysticks or four Paddles (or a combination) into a single virtal gamepad.

As an added bonus, it also includes support for the Atari games in Tesla automobiles so you can play them with real Atari controllers.

The XInput functionality is based on the excellent [MSF_FightStick XINPUT](https://github.com/zlittell/MSF-XINPUT) project 
by Zack "Reaper" Littell. I have provided source code and pre-compiled .HEX firmware.

Default mappings:

* P1 Joystick directions -> Dpad and Left Analog Stick.
* P1 Joystick button -> A
* P1 Joystick up -> B (Tesla Asteroids compatiblity)
* P1 Joystick down -> X (Tesla Asteroids compatibility)
* P2 Joystick -> Right Analog Stick
* P2 Joystick button -> Y
* Paddle 1 -> Left Analog X Axis
* Paddle 1 button -> LB
* Paddle 2 -> Left Analog Y Axis
* Paddle 2 button -> RB
* Paddle 3 -> Right Analog X Axis
* Paddle 3 button -> L3
* Paddle 4 -> Right Analog X Axis
* Paddle 4 button -> R3
