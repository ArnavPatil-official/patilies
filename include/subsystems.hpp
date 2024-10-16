#pragma once

#include "api.h"
#include "main.h"
using namespace pros;


// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor intake(11);
inline pros::Motor saketh_nandam(21);
inline pros::adi::DigitalOut clamp_digi('B');
inline pros::adi::DigitalOut henry_wo('A');
// inline pros::adi::DigitalIn limit_switch('A');
