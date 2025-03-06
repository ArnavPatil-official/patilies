#pragma once

#include "api.h"
#include "main.h"
using namespace pros;


// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor intake(11);
inline pros::Motor wall_stake_mech_1(-7); // 
inline pros::Motor wall_stake_mech_2(8); 
//inline pros::Motor_Group saketh_nandam ({wall_stake_mech_1, wall_stake_mech_2});
inline pros::adi::DigitalOut clamp_digi('A');
inline pros::adi::DigitalOut henry_wo('B');
inline pros::Rotation rotation_sensor(15);
// inline pros::adi::DigitalIn limit_switch('A');
inline pros::Motor leftFront(18);
inline pros::Motor leftTop(-20);
inline pros::Motor leftBack(-21);
inline pros::Motor rightFront(-17);
inline pros::Motor rightTop(12);
inline pros::Motor rightBack(13);
inline const int numStates = 4;
//make sure these are in centidegrees (1 degree = 100 centidegrees)
inline int states[numStates] = {0, 3500,8000,14500};
inline int currState = 0;
inline int target = 0;

inline void nextState() {
    currState += 1;
    if (currState == numStates) {
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
        wall_stake_mech_1.brake();
        return;
    }
    wall_stake_mech_1.move(velocity);
}