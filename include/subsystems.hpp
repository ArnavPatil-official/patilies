#pragma once

#include "api.h"
#include "main.h"
using namespace pros;


// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor intake(4);
// inline pros::Motor wall_stake_mech_1(10);
// inline pros::Motor wall_stake_mech_2(5);
// inline pros::Motor_group saketh_nandam({wall_stake_mech_1, wall_stake_mech_2});
inline pros::adi::DigitalOut clamp_digi('B');
inline pros::adi::DigitalOut henry_wo('A');
// inline pros::adi::DigitalIn limit_switch('A');
