#pragma once

#include "api.h"
#include "main.h"
using namespace pros;


// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor intake(5);
inline pros::Motor wall_stake_mech_1(7); // 
inline pros::Motor wall_stake_mech_2(1); // reverse
//inline pros::Motor_Group saketh_nandam ({wall_stake_mech_1, wall_stake_mech_2});
inline pros::adi::DigitalOut clamp_digi('A');
inline pros::adi::DigitalOut henry_wo('B');
inline pros::Rotation rotation_sensor(4);
// inline pros::adi::DigitalIn limit_switch('A');
