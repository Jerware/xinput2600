# xinput2600
XInput Adapter for Atari 2600 Controllers

<a href="images/x2600_angle.jpg"><img src="https://github.com/Jerware/xinput2600/blob/master/images/x2600_angle_small.jpg" width="400" height="300"></a><a href="images/x2600_top.jpg"><img src="https://github.com/Jerware/xinput2600/blob/master/images/x2600_top_small.jpg" width="400" height="300"></a>

This project was initially created for [Starlords](https://youtu.be/S8GnZouBUoo), 
a physical arcade game & cabinet developed by Tested.com and Other Ocean Interactive. This code, when paried with 
[the PCB available on OshPark](https://oshpark.com/shared_projects/ybyjPbuy), converts signals from original Atari 2600 controllers 
to XInput, combining either two Joysticks or four Paddles (or any combination) into a single virtual gamepad. The XInput functionality
is based on the excellent [MSF_FightStick XINPUT](https://github.com/zlittell/MSF-XINPUT) project by Zack "Reaper" Littell.

As a bonus, it also supports the hidden Atari games in Tesla automobiles so you can play them with a real Atari joystick.

I have provided source code and pre-compiled .HEX firmware. To flash the compiled firmware on a Teensy LC, use the official
[Teensy Loader](https://www.pjrc.com/teensy/loader.html) application.

**Note**: If you only want Joystick functionality (i.e. no Paddles), you don't need to include most of the components on the PCB. 
You'll only need the PCB, Teensy LC, D-Sub Plugs, and optionally the male & female headers. In this case, please install 
the "JoystickOnly" firmware.

**Here is the complete components list:**

* [PCB](https://oshpark.com/shared_projects/ybyjPbuy)
* [Teensy LC](https://www.pjrc.com/store/teensylc_pins.html)
* [D-Sub Plugs](https://www.digikey.com/product-detail/en/amphenol-icc-fci/LD09P13A4GX00LF/609-5183-ND/4997285) (2)
* [1 kOhm Resistors](https://www.digikey.com/product-detail/en/stackpole-electronics-inc/CF14JT1K00/CF14JT1K00CT-ND/1830350) (4)
* [0.1µF Capacitors](https://www.digikey.com/product-detail/en/murata-electronics-north-america/RDER71H104K0P1H03B/490-8815-ND/4770970) (4)
* [1 MegaOhm Resistor Array](https://www.digikey.com/product-detail/en/bourns-inc/4605X-101-105LF/4605X-101-105LF-ND/3787497)
* [LM324N OpAmp](https://www.digikey.com/product-detail/en/texas-instruments/LM324N/296-1391-5-ND/277627)
* [14 Position Female Headers](https://www.digikey.com/product-detail/en/sullins-connector-solutions/PPTC141LFBN-RC/S7012-ND/810152) (2)
* [2 Position Male Headers](https://www.digikey.com/product-detail/en/te-connectivity-amp-connectors/640456-2/A1921-ND/109003) (3) _Optional_

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
