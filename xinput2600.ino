/*
    XInput 2600 v20190125
    XInput Adapter for Atari 2600 Controllers
    Details: https://github.com/Jerware/xinput2600
    
    Based on the excellent MSF_FightStick XINPUT project by Zack "Reaper" Littell
    https://github.com/zlittell/MSF-XINPUT
*/

//Include the XINPUT library
#include <xinput.h>
// include the ResponsiveAnalogRead library
#include <ResponsiveAnalogRead.h>

ResponsiveAnalogRead analogA0(A0, false);
ResponsiveAnalogRead analogA1(A1, false);
ResponsiveAnalogRead analogA2(A2, false);
ResponsiveAnalogRead analogA3(A3, false);

//Define pins for later use
#define B1PIN 0 // P2 Down
#define B2PIN 1 // P2 Right
#define B3PIN 2 // P2 Left
#define B4PIN 3 // P2 Up
#define B5PIN 4 // P1 Up
#define B6PIN 5 // P1 Down
#define B7PIN 6 // P1 Left
#define B8PIN 7 // P1 Right
#define B9PIN 8 // P1 Fire
#define B10PIN 9 // P2 Fire
#define B11PIN 10 // Xbox START
#define B12PIN 11 // Xbox BACK
#define B13PIN 12 // Internal Reset
#define LEDPIN 13 // Teensy Onboard LED

// assume 1M Ohm resistors and official Atari 2600 controllers
int lowA0 = 0;
int lowA1 = 0;
int lowA2 = 0;
int lowA3 = 0;
int highA0 = 1500;
int highA1 = 1500;
int highA2 = 1500;
int highA3 = 1500;
int detectLevel = 2250;

boolean joystickOnly = true; // ignore paddles forever
boolean paddleP1 = false; // paddles plugged into P1
boolean paddleP2 = false; // paddles plugged into P2
int paddleDetectionThreshold = 500; // in ms
long paddleDetectionP1 = 0;
long paddleDetectionP2 = 0;

const int numReadings = 3;
int readingsA0[numReadings];
int readingsA1[numReadings];
int readingsA2[numReadings];
int readingsA3[numReadings];

boolean enableSmoothing = false; // Use ResponsiveAnalogRead Library
boolean enableFiltering = true; // Ignore reading if it matches any of the last numReadings

//Initiate the class and setup the LED pin
XINPUT controller(LED_ENABLED, LEDPIN);

void setup() {
  analogReadAveraging(32);
  analogReadResolution(12);

  float snap = .5;
  int res = 4096;
  analogA0.setAnalogResolution(res);
  analogA1.setAnalogResolution(res);
  analogA2.setAnalogResolution(res);
  analogA3.setAnalogResolution(res);
  analogA0.setSnapMultiplier(snap);
  analogA1.setSnapMultiplier(snap);
  analogA2.setSnapMultiplier(snap);
  analogA3.setSnapMultiplier(snap);

  //Set pin modes
  pinMode(B1PIN, INPUT_PULLUP);
  pinMode(B2PIN, INPUT_PULLUP);
  pinMode(B3PIN, INPUT_PULLUP);
  pinMode(B4PIN, INPUT_PULLUP);
  pinMode(B5PIN, INPUT_PULLUP);
  pinMode(B6PIN, INPUT_PULLUP);
  pinMode(B7PIN, INPUT_PULLUP);
  pinMode(B8PIN, INPUT_PULLUP);
  pinMode(B9PIN, INPUT_PULLUP);
  pinMode(B10PIN, INPUT_PULLUP);
  pinMode(B11PIN, INPUT_PULLUP);
  pinMode(B12PIN, INPUT_PULLUP);
  pinMode(B13PIN, INPUT_PULLUP);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  delay(1000); 
}

void loop() {

  // reset?
  if (digitalRead(B13PIN) == LOW)
  {
    paddleP1 = false;
    paddleP2 = false;
  }

  int readingA0 = 0;
  int readingA1 = 0;
  int readingA2 = 0;
  int readingA3 = 0;

  if (enableSmoothing)
  {
    analogA0.update();
    analogA1.update();
    analogA2.update();
    analogA3.update();
    readingA0 = analogA0.getValue();
    readingA1 = analogA1.getValue();
    readingA2 = analogA2.getValue();
    readingA3 = analogA3.getValue();
  }

  else
  {
    readingA0 = analogRead(A0);
    readingA1 = analogRead(A1);
    readingA2 = analogRead(A2);
    readingA3 = analogRead(A3);
  }

  // ignore reading if it matches a recent one
  // (damnit why didn't I make a paddle class)
  if (enableFiltering)
  {
    // A0
    boolean newReading = true;
    for (int i=0; i<numReadings; i++)
    {
      // duplicate?
      if (readingA0 == readingsA0[i])
      {
        readingA0 = readingsA0[0];
        newReading = false;
        break;
      }
    }
    // new reading!
    if (newReading)
    {
      for (int i=numReadings-1; i>0; i--)
      {
        readingsA0[i] = readingsA0[i-1];
      }
      readingsA0[0] = readingA0;
    }
    
    // A1
    newReading = true;
    for (int i=0; i<numReadings; i++)
    {
      if (readingA1 == readingsA1[i])
      {
        readingA1 = readingsA1[0];
        newReading = false;
        break;
      }
    }
    if (newReading)
    {
      for (int i=numReadings-1; i>0; i--)
      {
        readingsA1[i] = readingsA1[i-1];
      }
      readingsA1[0] = readingA1;
    }
    
    // A2
    newReading = true;
    for (int i=0; i<numReadings; i++)
    {
      if (readingA2 == readingsA2[i])
      {
        readingA2 = readingsA2[0];
        newReading = false;
        break;
      }
    }
    if (newReading)
    {
      for (int i=numReadings-1; i>0; i--)
      {
        readingsA2[i] = readingsA2[i-1];
      }
      readingsA2[0] = readingA2;
    }
    
    // A3
    newReading = true;
    for (int i=0; i<numReadings; i++)
    {
      if (readingA3 == readingsA3[i])
      {
        readingA3 = readingsA3[0];
        newReading = false;
        break;
      }
    }
    if (newReading)
    {
      for (int i=numReadings-1; i>0; i--)
      {
        readingsA3[i] = readingsA3[i-1];
      }
      readingsA3[0] = readingA3;
    }    
  }

  int spinP1;
  int spinP2;
  int spinP3;
  int spinP4;

  // Monitor controller connection for paddles
  // Analog readings above "detectLevel" should mean paddle is disconnected
  // P1 Paddles
  if (readingA0 > detectLevel && readingA1 > detectLevel && paddleP1)
  {
    // start detection timer
    if (paddleDetectionP1 == 0)
    {
      paddleDetectionP1 = millis() + paddleDetectionThreshold;
    }
    // disable paddles
    else if (millis() > paddleDetectionP1)
    {
      paddleP1 = false;
    }
  }

  else if (readingA0 <= detectLevel && readingA1 <= detectLevel && !paddleP1)
  {
    // start detection timer
    if (paddleDetectionP1 == 0)
    {
      paddleDetectionP1 = millis() + paddleDetectionThreshold;
    }
    // enable paddles
    else if (millis() > paddleDetectionP1)
    {
      paddleP1 = true;

      // enable/disable smoothing by holding one of the P1 paddle buttons on startup
      if (digitalRead(B7PIN) == LOW || digitalRead(B8PIN) == LOW) enableSmoothing = !enableSmoothing;
    }
  }

  // P2 Paddles
  if (readingA2 > detectLevel && readingA3 > detectLevel && paddleP2)
  {
    // start detection timer
    if (paddleDetectionP2 == 0)
    {
      paddleDetectionP2 = millis() + paddleDetectionThreshold;
    }
    // disable paddles
    else if (millis() > paddleDetectionP2)
    {
      paddleP2 = false;
    }
  }

  else if (readingA2 <= detectLevel && readingA3 <= detectLevel && !paddleP2)
  {
    // start detection timer
    if (paddleDetectionP2 == 0)
    {
      paddleDetectionP2 = millis() + paddleDetectionThreshold;
    }
    // enable paddles
    else if (millis() > paddleDetectionP2)
    {
      paddleP2 = true;
    }
  }

  if (joystickOnly)
  {
    paddleP1 = false;
    paddleP2 = false;
  }

  // reset paddle detection timers if normal conditions detected
  if (readingA0 > detectLevel && readingA1 > detectLevel && !paddleP1 && paddleDetectionP1 > 0) paddleDetectionP1 = 0;
  else if (readingA0 <= detectLevel && readingA1 <= detectLevel && paddleP1 && paddleDetectionP1 > 0) paddleDetectionP1 = 0;
  if (readingA2 > detectLevel && readingA3 > detectLevel && !paddleP2 && paddleDetectionP2 > 0) paddleDetectionP2 = 0;
  else if (readingA2 <= detectLevel && readingA3 <= detectLevel && paddleP2 && paddleDetectionP2 > 0) paddleDetectionP2 = 0;

  // send paddle positions
  if (!paddleP1)
  {
    spinP1 = 0;
    spinP2 = 0;
  }

  else
  {
    spinP1 = map(readingA0, lowA0, highA0, 32000, -32000);
    spinP2 = map(readingA1, lowA1, highA1, -32000, 32000);
  }

  if (!paddleP2)
  {
    spinP3 = 0;
    spinP4 = 0;
  }

  else
  {
    spinP3 = map(readingA2, lowA2, highA2, 32000, -32000);
    spinP4 = map(readingA3, lowA3, highA3, -32000, 32000);
  }
  
  // floor and ceiling
  if (spinP1 < -32000) spinP1 = -32000;
  else if (spinP1 > 32000) spinP1 = 32000;
  if (spinP2 < -32000) spinP2 = -32000;
  else if (spinP2 > 32000) spinP2 = 32000;
  if (spinP3 < -32000) spinP3 = -32000;
  else if (spinP3 > 32000) spinP3 = 32000;
  if (spinP4 < -32000) spinP4 = -32000;
  else if (spinP4 > 32000) spinP4 = 32000;

  controller.stickUpdate(STICK_LEFT, spinP1, spinP2); // P1/P2 Pot
  controller.stickUpdate(STICK_RIGHT, spinP3, spinP4); // P3/P4 Pot

// unused additional paddles
//  int spinP5 = map(analogRead(A4), 1, 1023, 0, 255);
//  int spinP6 = map(analogRead(A5), 1, 1023, 0, 255);
//  controller.triggerUpdate(spinP5, spinP6);

  //Read pin values
  int buttonP1 = digitalRead(B1PIN);
  int buttonP2 = digitalRead(B2PIN);
  int buttonP3 = digitalRead(B3PIN);
  int buttonP4 = digitalRead(B4PIN);
  int buttonP5 = digitalRead(B5PIN);
  int buttonP6 = digitalRead(B6PIN);
  int buttonP7 = digitalRead(B7PIN);
  int buttonP8 = digitalRead(B8PIN);
  int buttonP9 = digitalRead(B9PIN);
  int buttonP10 = digitalRead(B10PIN);
  int buttonP11 = digitalRead(B11PIN);
  int buttonP12 = digitalRead(B12PIN);

  // Joystick connected?
  if (!paddleP1)
  {
    // P1 Joystick maps to Dpad and Left Analog Stick and ABX Buttons (Tesla Asteroids compatibility)
    controller.dpadUpdate(!buttonP5, !buttonP6, !buttonP7, !buttonP8); // P1 up, down, left, right
    if (!buttonP5) spinP2 = 32000; // up
    if (!buttonP6) spinP2 = -32000; // down
    if (!buttonP7) spinP1 = -32000; // left
    if (!buttonP8) spinP1 = 32000; // right
    controller.stickUpdate(STICK_LEFT, spinP1, spinP2);
    controller.buttonUpdate(BUTTON_A, !buttonP9); // Fire -> A
    controller.buttonUpdate(BUTTON_B, !buttonP5); // Up -> B
    controller.buttonUpdate(BUTTON_X, !buttonP6); // Down -> X
  }

  // support paddle buttons
  else
  {
    controller.buttonUpdate(BUTTON_LB, !buttonP7); // Paddle 1 Fire -> LB    
    controller.buttonUpdate(BUTTON_RB, !buttonP8); // Paddle 2 Fire -> RB
  }

  if (!paddleP2)
  {
    // P2 Joystick maps to Right Analog Stick and Y Button
    if (!buttonP4) spinP4 = 32000; // up
    if (!buttonP1) spinP4 = -32000; // down
    if (!buttonP3) spinP3 = -32000; // left
    if (!buttonP2) spinP3 = 32000; // right
    controller.stickUpdate(STICK_RIGHT, spinP3, spinP4);
    controller.buttonUpdate(BUTTON_Y, !buttonP10); // P2 UP Fire -> Y
  }

  // support paddle buttons
  else
  {
    controller.buttonUpdate(BUTTON_L3, !buttonP3); // Paddle 3 Fire -> L3
    controller.buttonUpdate(BUTTON_R3, !buttonP2); // Paddle 4 Fire -> R3
  }

  // Special pins
  controller.buttonUpdate(BUTTON_BACK, !buttonP12); // Xbox BACK
  controller.buttonUpdate(BUTTON_START, !buttonP11); // Xbox START

  //Update the LED display
  controller.LEDUpdate();

  //Send data
  controller.sendXinput();

  //Receive data
  controller.receiveXinput();
}
