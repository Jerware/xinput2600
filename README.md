# xinput2600
XInput Adapter for Atari 2600 Controllers

This project was initially created for [Starlords](https://www.tested.com/premium/852029-bits-atoms-starlords-arcade-cabinet-part-1/), 
a physical arcade game & cabinet developed by Tested.com and Other Ocean Interactive. This code, when paried with 
[the PCB available on OshPark](https://oshpark.com/shared_projects/ybyjPbuy), converts signals from original Atari 2600 controllers 
to XInput, combining either two Joysticks or four Paddles (or any combination) into a single virtual gamepad.

As an added bonus, it also supports the hidden Atari games in Tesla automobiles so you can play them with real Atari controllers.

**NOTE**: If you only need joystick functionality, you don't need to install all of the extra components on the PCB. You only need the D-SUB Plug controller ports and a Teensy LC. For paddle support, you need everything. Here is the complete components list:

* [Teensy LC](https://www.pjrc.com/store/teensylc.html)
* [D-SUB PLUGS](https://www.digikey.com/product-detail/en/amphenol-icc-fci/LD09P13A4GX00LF/609-5183-ND/4997285) (2)
* [1 kOhm Resistors](https://www.digikey.com/product-detail/en/stackpole-electronics-inc/CF14JT1K00/CF14JT1K00CT-ND/1830350) (4)
* [10uF Capacitors](https://www.digikey.com/product-detail/en/tdk-corporation/FG14X7R1A106KRT06/445-173132-1-ND/5811737) (4)
* [1 MegaOhm Resistor Array](https://www.digikey.com/product-detail/en/bourns-inc/4605X-101-105LF/4605X-101-105LF-ND/3787497)
* [LM324N OpAmp](https://www.digikey.com/product-detail/en/texas-instruments/LM324N/296-1391-5-ND/277627)
* [14 Position Female Headers](https://www.digikey.com/product-detail/en/sullins-connector-solutions/PPTC141LFBN-RC/S7012-ND/810152) (2)
* [2 Position Male Headers](https://www.digikey.com/product-detail/en/te-connectivity-amp-connectors/640456-2/A1921-ND/109003) (3)

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
