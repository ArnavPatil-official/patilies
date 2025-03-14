#pragma once

#include "api.h"
#include "main.h"
using namespace pros;


// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor intake(14);
inline pros::Motor wall_stake_mech_11(-18); // 
inline pros::Motor wall_stake_mech_22(19); 
//inline pros::Motor_Group saketh_nandam ({wall_stake_mech_1, wall_stake_mech_2});
inline pros::adi::DigitalOut clamp_digi('A');
inline pros::adi::DigitalOut henry_wo('B');
inline pros::Rotation rotation_sensor(12);
// inline pros::adi::DigitalIn limit_switch('A');
// inline pros::Motor leftFront(18);
// inline pros::Motor leftTop(-20);
// inline pros::Motor leftBack(-21);
// inline pros::Motor rightFront(-17);
// inline pros::Motor rightTop(12);
// inline pros::Motor rightBack(13);
inline const int numStates = 6;
//make sure these are in centidegrees (1 degree = 100 centidegrees)
inline int states[numStates] = {0, 3500, 8000, 17750, 18500, 24500};
inline int currState;
inline int target;
inline pros::Optical optical_sensor(1);
// Tracking wheel encoder
//inline pros::Rotation track(5);  // Adjust port number as needed

// Create tracking wheel and odom objects using EZ-Template
inline ez::tracking_wheel left_tracking(-5, 2.75, 2.5); // 2.75" wheel, -1 reverses direction if needed
//inline ez::Odom odom(&left_tracking); // Initialize odom with tracking wheel



inline void nextState() {
    currState += 1;
    if (currState == numStates) {
        currState = 0;
    }
    target = states[currState];
}
inline void setState(int set) {
    currState = set;
    if (currState >= numStates) {
        currState = 0;
    }
    target = states[currState];
}
inline int threshold = 200;
inline void liftControl() {
    double kp = 0.014;
    double error = target - rotation_sensor.get_position();
    double velocity = kp * error;
    if (abs(error) < threshold) {
        wall_stake_mech_11.brake();
        wall_stake_mech_22.brake();
        return;
    }
    wall_stake_mech_11.move(velocity);
    wall_stake_mech_22.move(velocity);
}