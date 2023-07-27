/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\maste                                            */
/*    Created:      Tue Jul 25 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Left_m               motor         1               
// Right_m              motor         2               
// ultrasonic           sonar         G, H            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
const double pi = 3.14159265358979323846;
const float circumfrence = 4*pi;
const int track_width = 11;
const float degperin = 360 / circumfrence;
const float gear = 5;
const float runningrpm = 200;

// PID Parameters 

const float mindrive = 50;
const float maxdrive = 500;
const float cautiondiff = 2;

void pid_run(float stopdist) {
  if (ultrasonic.distance(inches) > stopdist) {
    Right_m.spin(reverse);
    Left_m.spin(forward);
  }
  while (ultrasonic.distance(inches) > stopdist) {
    // Get the distance to start slowing down
    float cautiondist = stopdist + cautiondiff;
    // Create an inverted parabola of running speed - Calculate slope
    float slope = (mindrive - maxdrive)/ pow((stopdist - cautiondist), 2);
    // Make the equation and plug in the distance
    float speeds = slope * pow((ultrasonic.distance(inches) - cautiondist), 2) + maxdrive;
    // Change the speeds of the motors running
    Right_m.setVelocity(speeds, rpm);
    Left_m.setVelocity(speeds, rpm);
  }
  // Once the destination is reached then stop the motors and return the velocity to its default value
  Right_m.stop();
  Left_m.stop();
  Right_m.setVelocity(runningrpm, rpm);
  Left_m.setVelocity(runningrpm, rpm);
}

void forw(float inches, float speed) {
  float rotationDeg = degperin * inches * gear;
  rotationDeg = rotationDeg - 0.25;
  Right_m.spinFor(reverse, rotationDeg, degrees, speed, velocityUnits::rpm, false);
  Left_m.spinFor(forward, rotationDeg, degrees, speed, velocityUnits::rpm);

}

void reve(float inches, float speed) {
  float rotationDeg = degperin * inches * gear;
  rotationDeg = rotationDeg - 0.25;
  Right_m.spinFor(forward, rotationDeg, degrees, speed, velocityUnits::rpm, false);
  Left_m.spinFor(reverse, rotationDeg, degrees, speed, velocityUnits::rpm);

}

void left_turn(float deg, float speed) {
  float turnDeg = deg * track_width / 4 * gear;
  Right_m.spinFor(forward, turnDeg, degrees, speed, velocityUnits::rpm, false);
  Left_m.spinFor(forward, turnDeg, degrees, speed, velocityUnits::rpm);

}

void right_turn(float deg, float speed) {
  float turnDeg = deg * track_width / 4 * gear;
  Right_m.spinFor(reverse, turnDeg, degrees, speed, velocityUnits::rpm, false);
  Left_m.spinFor(reverse, turnDeg, degrees, speed, velocityUnits::rpm);

}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  
}
