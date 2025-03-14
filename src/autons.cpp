#include "main.h"
#include "subsystems.hpp"
#include "autons.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 127;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

///
// Constants
///

void default_constants() {
  //chassis.pid_drive_constants_set(20.0, 0.0, 100.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_drive_constants_set(15, 0.0, 138.0);
  chassis.pid_heading_constants_set(6.0, 0.0, 23.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants

  chassis.pid_turn_exit_condition_set(130_ms, 1_deg, 120_ms, 7_deg, 160_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(50_ms, 3_deg, 50_ms, 7_deg, 100_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(100_ms, 1_in, 125_ms, 3_in, 170_ms, 500_ms);

  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  chassis.slew_drive_constants_set(7_in, 80);
}

///
// Drive Example
///


// const int numStates_a = 4;
// //make sure these are in centidegrees (1 degree = 100 centidegrees)
// int states_a[numStates_a] = {0, 3500,8000,14500};
// int currState_a = 0;
// int target_a = 0;

// void nextState_a() {
//     currState_a += 1;
//     if (currState_a == numStates_a) {
//         currState_a = 0;
//     }
//     target_a = states_a[currState_a];
// }
// int threshold_a = 200;
// void liftWait() {
//     while (abs(target_a - rotation_sensor.get_position()) >= threshold_a) {
//         pros::delay(10);
//     }
// }
// void liftControl_a() {
//     double kp_a = 0.014;
//     double error_a = target_a - rotation_sensor.get_position();
//     double velocity_a = kp_a * error_a;
//     if (abs(error_a) < threshold_a) {
//         wall_stake_mech_1.brake();
//         return;
//     }
//     wall_stake_mech_1.move(velocity_a);
// }
// void lift(int input) {
//   target_a = input;
// }

// pros::Task liftAutonControlTask([]{
//         while (true) {
//             liftControl_a();
//             pros::delay(10);
//         }
// });
int ring_set = 3500;
int middle_stage = 8000;
int score = 14500;
void lift(int input) {
  target = input;
}
bool detect_red() {
    optical_sensor.set_led_pwm(100); // Turn on LED at full brightness
    
    // Get hue from 0-359
    double brightness = optical_sensor.get_brightness();
    
    // Red hue is around 0/360, allow some tolerance
    // Check if hue is close to 0 or 360
    if (brightness > 0.1) {
        return true;
    }
    return false;
}
void skills() { // red
  chassis.pid_turn_behavior_set(ez::shortest);
  chassis.pid_odom_behavior_set(ez::shortest);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_drive_set(-1.5_in, DRIVE_SPEED, false);
  chassis.pid_wait();
  setState(ALLIANCE_SCORE);
  pros::delay(600);
  chassis.pid_drive_set(-7_in, DRIVE_SPEED, false);
  chassis.pid_wait();
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-15_in, 63, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-5_in, 63, true); 
  chassis.pid_wait();
  clamp_digi.set_value(true);
  pros::delay(700);
  chassis.pid_turn_set(180_deg, TURN_SPEED);
  intake.move(127);
  chassis.pid_wait();
  setState(DEFAULT);
  intake.move(-127);
  chassis.pid_drive_set(19_in, 85, true);
  chassis.pid_wait();
  pros::delay(200);
  chassis.pid_turn_set(208_deg, TURN_SPEED);
  chassis.pid_wait();
  pros::delay(600);
  setState(LOAD);
  chassis.pid_drive_set(43_in, 66);
  chassis.pid_wait();
  pros::delay(600);
  chassis.pid_drive_set(-2_in, 66);
  chassis.pid_wait();
  chassis.pid_turn_set(180_deg, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  intake.brake();
  setState(ALIGN);
  intake.move(127);
  chassis.pid_turn_set(230_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move(-127);
  chassis.pid_drive_set(15_in, 50, true);
  chassis.pid_wait();
  chassis.pid_turn_set(270_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(4.5, 50);
  chassis.pid_wait();
  setState(WALL_SCORE);
  pros::delay(500);
  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setState(ALIGN);
  intake.move(-99);
  pros::delay(200);
  chassis.pid_turn_set(360_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(34_in, 60, true);
  chassis.pid_wait();
  pros::delay(200);
  chassis.pid_drive_set(17_in, 60, true);
  chassis.pid_wait();
  pros::delay(200);
  chassis.pid_drive_set(-25_in, 60, true);
  chassis.pid_wait();
  intake.move(127);
  pros::delay(100);
  intake.move(-127);
  chassis.pid_turn_set(330_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(16_in, 60, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-12_in, 60, true);
  chassis.pid_wait();
  chassis.pid_turn_set(150_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-22_in, 60, true);
  chassis.pid_wait();
  clamp_digi.set_value(false);
  pros::delay(200);
  chassis.pid_drive_set(14, 55, true);
  chassis.pid_wait();
  // chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  // chassis.drive_angle_set(0_deg);
  // chassis.pid_odom_set(-1.5_in,DRIVE_SPEED,false);
  // chassis.pid_wait();
  // setState(ALLIANCE_SCORE);
  //  pros::delay(700);
  // pros::delay(600);
  // chassis.pid_drive_set(-6.5_in,DRIVE_SPEED,false);
  // chassis.pid_wait();
  // chassis.pid_turn_set(90_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-15_in, 63, true);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-5_in, 63, true); 
  // chassis.pid_wait();
  // chassis.pid_odom_set({{-15_in, -8_in, 90_deg}, fwd, 110});
  // chassis.pid_wait();
  // chassis.pid_odom_set(-5_in,40,false);
  // chassis.pid_wait();
  // clamp_digi.set_value(true);
  // chassis.pid_turn_set(180_deg, TURN_SPEED);
  // chassis.pid_wait();
  // setState(DEFAULT);
  // intake.move(-127);
  // chassis.pid_odom_set(19_in, 85, true);
  // chassis.pid_wait();
  // pros::delay(200);
  
  // pros::delay(700);
  // pros::delay(600);
  // chassis.pid_drive_set(-6.5_in,DRIVE_SPEED,false);
  // chassis.pid_wait();
  // chassis.pid_turn_set(90_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-15_in, 63, true);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-5_in, 63, true); 
  // chassis.pid_wait();
  // 
  // chassis.pid_turn_set(180_deg, TURN_SPEED);
  // chassis.pid_wait();
  // setState(DEFAULT);
  // intake.move(-127);
  // chassis.pid_drive_set(19_in, 85, true);
  // chassis.pid_wait();
  // pros::delay(200);
  // chassis.pid_turn_relative_set(27_deg, TURN_SPEED);
  // chassis.pid_wait();
  // pros::delay(600);
  // setState(LOAD);
  // chassis.pid_drive_set(43_in, 66);
  // chassis.pid_wait();
  // pros::delay(600);
  // chassis.pid_drive_set(-2_in, 66);
  // chassis.pid_wait();
  // chassis.pid_turn_set(180_deg,DRIVE_SPEED,true);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-24_in,DRIVE_SPEED,true);
  // chassis.pid_wait();
  // intake.brake();
  // setState(ALIGN);
  // chassis.pid_turn_set(230_deg,TURN_SPEED);
  // chassis.pid_wait();
  // intake.move(-127);
  // chassis.pid_drive_set(13.5_in,50,true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(270_deg,TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(4,50);
  // chassis.pid_wait();
  // setState(WALL_SCORE);
  // pros::delay(500);
  // chassis.pid_drive_set(-9.5_in,DRIVE_SPEED,true);
  // chassis.pid_wait();
  // setState(ALIGN);
  // intake.move(-99);
  // pros::delay(200);
  // chassis.pid_turn_set(360_deg,TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(34_in,60,true);
  // chassis.pid_wait();
  // pros::delay(200);
  // chassis.pid_drive_set(12_in,60,true);
  // chassis.pid_wait();
  // pros::delay(200);
  // chassis.pid_drive_set(-20_in,60,true);
  // chassis.pid_wait();
  // intake.move(127);
  // pros:delay(100);
  // intake.move(-127);
  // chassis.pid_turn_set(330_deg,TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(12_in,60,true);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-8_in,60,true);
  // chassis.pid_wait();
  // chassis.pid_turn_relative_set(180_deg,TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-19_in,60,true);
  // chassis.pid_wait();
  // clamp_digi.set_value(false);
  // pros::delay(200);
  // chassis.pid_drive_set(14,55,true);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-12.5_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(-30_deg,TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-21_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // pros::delay(600);
  // clamp_digi.set_value(true);
  // pros::delay(800);
  
  // chassis.pid_turn_set(-90_deg, TURN_SPEED);
  // chassis.pid_wait();
  // pros::delay(100);
  // intake.move(-127);
  // chassis.pid_drive_set(21_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // intake.move(127);
  // pros::delay(100);
  // intake.move(-127);
  // chassis.pid_drive_set(-21_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(-180_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-30_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // clamp_digi.set_value(false);
  // pros::delay(700);
  // chassis.pid_drive_set(6_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(-90_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-37_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(-30_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // pros::delay(600);
  // clamp_digi.set_value(true);
  // pros::delay(700);
  // intake.move(-127);
  // chassis.pid_turn_set(95_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(25, 45, true);
  // chassis.pid_wait();
  // pros::delay(575);
  // intake.move(0);
  // chassis.pid_turn_set(-95_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(38_in,DRIVE_SPEED,false);
  // chassis.pid_wait();
  // chassis.pid_turn_set(-189_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(43_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_drive_set(6_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(-45_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(14_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(22_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-7_in, 45, true);
  // chassis.pid_wait_until(-4_in);
  // clamp_digi.set_value(false);
  // chassis.pid_wait();
  // pros::delay(500);
  // chassis.pid_drive_set(32_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  //ladybrown up
  // saketh_anandam(127);
  // chassis.drive_angle_set(0_deg);
  // chassis.pid_drive_set(-5_in,85,true);
  // chassis.pid_wait();
  // stop_saketh_anandam();
  // intake.move(-127);
  // pros::delay(1500);
  // chassis.pid_drive_set(14_in,85,true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(90_deg,TURN_SPEED);
  // chassis.pid_wait();
  // intake.brake();
  // // stake_absolute(3175,127);
  // chassis.pid_drive_set(-24_in,DRIVE_SPEED,true);
  // chassis.pid_wait_until(-10_in);
  // chassis.pid_speed_max_set(45);
  // chassis.pid_wait();
  // clamp_digi.set_value(true);
  // chassis.pid_turn_set(0_deg,TURN_SPEED);
  // chassis.pid_wait();
  // intake.move(-127);
  // chassis.pid_drive_set(18_in,DRIVE_SPEED,true);
  // chassis.pid_wait();
  // intake.move(-127);
  // //backwards is intake
  // pros::delay(450);
  // chassis.pid_turn_relative_set(-45_deg,TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(34_in,DRIVE_SPEED,true);
  // chassis.pid_wait();
  // pros::delay(500);
  // chassis.pid_turn_set(-188_deg,TURN_SPEED);
  // chassis.pid_wait();
  // pros::delay(250);
  // chassis.pid_drive_set(15_in,DRIVE_SPEED,true);
  // chassis.pid_wait();
  // intake.move(-127);
  // chassis.pid_turn_set(-180_deg,TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(17.5_in,95,true);
  // chassis.pid_wait();
  // pros::delay(450);
  // chassis.pid_drive_set(13.5_in,95,true);
  // chassis.pid_wait();
  // intake.move(-127);
  // chassis.pid_turn_set(-45_deg,TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(13_in,95,true);
  // chassis.pid_wait();
  // pros::delay(750);
  // chassis.pid_turn_set(25_deg,TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-14_in,DRIVE_SPEED/2,true);
  // chassis.pid_wait_until(-10_in);
  // clamp_digi.set_value(false);
  // chassis.pid_wait();
  // pros::delay(750);
  // chassis.pid_turn_set(35_deg,TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(14_in,DRIVE_SPEED);
  // chassis.pid_wait();
  // chassis.pid_turn_set(-90_deg,TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-72_in,DRIVE_SPEED);
  // chassis.pid_wait();
  //points.code(31);
  // chassuf.oidaw-***.. 
  // asuii__ .. 
  // o2 .. 
  // 10ll l{{ 11#11011##}}
  // -- ++ ad.to. param 
  // param..0
  // ### 1011
  // lf8..bin
  // [\\oidan]
  // ENCRYPT..[##err.no{11011101**110}]
  // o2.joint ...

}
void blue_awp() {
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_odom_set(-1.5_in,DRIVE_SPEED,false);
  chassis.pid_wait();
  setState(ALLIANCE_SCORE);
  pros::delay(600);
  chassis.pid_odom_set(-6.5_in,DRIVE_SPEED,false);
  chassis.pid_wait();
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_odom_set(-15_in, 63, true);
  chassis.pid_wait();
  chassis.pid_odom_set(-5_in, 63, true); 
  chassis.pid_wait();
  clamp_digi.set_value(true);
  pros::delay(700);
  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();
  setState(DEFAULT);
  intake.move(-127);
  chassis.pid_odom_set(19_in, 85, true);
  chassis.pid_wait();
  pros::delay(200);
  chassis.pid_turn_relative_set(27_deg, TURN_SPEED);
  chassis.pid_wait();
  pros::delay(600);
  setState(LOAD);
  chassis.pid_odom_set(43_in, 66);
  chassis.pid_wait();
  pros::delay(600);
  chassis.pid_odom_set(-2_in, 66);
  chassis.pid_wait();
  chassis.pid_turn_set(180_deg,DRIVE_SPEED,true);
  chassis.pid_wait();
  chassis.pid_odom_set(-24_in,DRIVE_SPEED,true);
  chassis.pid_wait();
  intake.brake();
  setState(ALIGN);
  chassis.pid_turn_set(230_deg,TURN_SPEED);
  chassis.pid_wait();
  intake.move(-127);
  chassis.pid_odom_set(16_in,50,true);
  chassis.pid_wait();
  chassis.pid_turn_set(270_deg,TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_odom_set(3.5,50);
  chassis.pid_wait();
  setState(WALL_SCORE);
  pros::delay(500);
  chassis.pid_odom_set(-10_in,DRIVE_SPEED,true);
  chassis.pid_wait();
  setState(ALIGN);
  intake.move(-99);
  pros::delay(200);
  chassis.pid_turn_set(360_deg,TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_odom_set(34_in,60,true);
  chassis.pid_wait();
  pros::delay(200);
  chassis.pid_odom_set(12_in,60,true);
  chassis.pid_wait();
  pros::delay(200);
  chassis.pid_odom_set(-20_in,60,true);
  chassis.pid_wait();
  intake.move(127);
  pros:delay(100);
  intake.move(-127);
  chassis.pid_turn_set(330_deg,TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_odom_set(12_in,60,true);
  chassis.pid_wait();
  chassis.pid_odom_set(-8_in,60,true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(180_deg,TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_odom_set(-19_in,60,true);
  chassis.pid_wait();
  clamp_digi.set_value(false);
  pros::delay(200);
  chassis.pid_odom_set(14,55,true);
  chassis.pid_wait();
  // lift(0);
  // chassis.drive_angle_set(0_deg);
  // chassis.pid_drive_set(-6_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // intake.move(-100);
  // pros::delay(400);
  // chassis.pid_drive_set(13.5_in, DRIVE_SPEED, true); 
  // chassis.pid_wait();
  // chassis.pid_turn_set(90_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-24_in, 45, true);
  // chassis.pid_wait();
  // chassis.pid_wait_until(-8_in);
  // chassis.pid_speed_max_set(45);
  // clamp_digi.set_value(true);
  // chassis.pid_drive_set(-3_in, 83, true);
  // chassis.pid_wait();
  // pros::delay(500);
  // chassis.pid_drive_set(4_in, 83, true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(0_deg, 45);
  // chassis.pid_wait();
  // intake.move(-90);
  // chassis.pid_drive_set(25_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // pros::delay(550);
  // chassis.pid_turn_set(-90_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(25_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(-26_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(25_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // pros::delay(350);
  // chassis.pid_drive_set(-25_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(180_deg, TURN_SPEED);
  // chassis.pid_wait();
  // intake.move(127);
  // pros:delay(300);
  // intake.move(-127);
  // chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // pros::delay(200);
  // chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(315_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-5_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(30_deg, TURN_SPEED);
  // chassis.pid_wait();
  // clamp_digi.set_value(false);
  // chassis.pid_drive_set(-8_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_wait_until(-3_in);
  // pros::delay(700);
  // chassis.pid_drive_set(14_in,DRIVE_SPEED,true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(-90_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-62_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_speed_max_set(45);
  // chassis.pid_drive_set(-8_in, 45, true); 
  // chassis.pid_wait_until(-3_in);
  // clamp_digi.set_value(true);
  // pros::delay(500);
  // chassis.pid_wait();
  // chassis.pid_turn_set(90_deg,TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(14_in,DRIVE_SPEED,true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(-30_deg,TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-5_in,DRIVE_SPEED);
  // chassis.pid_wait();
  // clamp_digi.set_value(false);
  // pros::delay(400);
  // chassis.pid_drive_set(5_in,DRIVE_SPEED);
  // chassis.pid_wait();
  // lift(ring_set);
  // chassis.pid_turn_set(0_deg,TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(22_in,DRIVE_SPEED,true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(18_deg,TURN_SPEED);
  // chassis.pid_wait();
  // lift(score);
  // chassis.pid_drive_set(-13.5_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(30_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-12_in, DRIVE_SPEED/2, true);
  // chassis.pid_wait();
  // clamp_digi.set_value(true); 
  // chassis.pid_drive_set(-3_in, DRIVE_SPEED/2, true);
  // chassis.pid_wait();
  //  intake.move(-127/1.25);
  // chassis.pid_turn_set(103_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(15_in, DRIVE_SPEED, true); 
  // chassis.pid_wait();
  // chassis.pid_turn_set(160_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-30_in, DRIVE_SPEED, true);
  // chassis.pid_wait_until(-23_in);
  // clamp_digi.set_value(false);
  // chassis.pid_wait();
  // chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(90_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-47.4_in, DRIVE_SPEED, true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(30_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-14_in, DRIVE_SPEED/1.25, true);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-4_in, DRIVE_SPEED/2, true);
  // chassis.pid_wait();
  // clamp_digi.set_value(true);
  // chassis.pid_drive_set(-13.2_in,DRIVE_SPEED,false);
  // chassis.pid_wait();
  // chassis.pid_turn_set(90_deg,TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-23_in,DRIVE_SPEED/4,false);
  // chassis.pid_wait();
  // chassis.pid_drive_set(1.9_in,DRIVE_SPEED/4,false);
  // chassis.pid_wait();p
  // intake.move(-127);

}
void red_awp() { // match
  chassis.pid_drive_set(-12.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(30_deg,TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-21_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(-13_in);
  chassis.pid_speed_max_set(45);
  chassis.pid_wait();
  pros::delay(600);
  clamp_digi.set_value(true);
  pros::delay(300);
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
  pros::delay(100);
  intake.move(-127);
  chassis.pid_drive_set(21_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  intake.move(127);
  pros::delay(100);
  intake.move(-127);
  chassis.pid_drive_set(-21_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-30_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(-14_in);
  chassis.pid_speed_max_set(45);
  chassis.pid_wait();
  clamp_digi.set_value(false);
  pros::delay(300);
  chassis.pid_drive_set(6_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-37_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(30_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(600);
  clamp_digi.set_value(true);
  pros::delay(700);
  intake.move(-127);
  chassis.pid_turn_set(-95_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(25, 45, true);
  chassis.pid_wait();
  pros::delay(575);
  intake.move(0);
  chassis.pid_turn_set(95_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(38_in,DRIVE_SPEED,false);
  chassis.pid_wait();

}




void drive_example() { // red half
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  chassis.pid_drive_set(-12.5_in, 45, true);
  chassis.pid_wait();
  chassis.pid_turn_set(-30_deg,TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-23_in, 45, true);
  chassis.pid_wait();
  pros::delay(600);
  clamp_digi.set_value(true);
  pros::delay(800);
  
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();
  pros::delay(100);
  intake.move(-127);
  chassis.pid_drive_set(21_in, 45, true);
  chassis.pid_wait();
  intake.move(127);
  pros::delay(100);
  intake.move(-127);
  chassis.pid_drive_set(-21_in, 45, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-12_in,45,true);
  //lift(11750);
  chassis.pid_turn_set(-190_deg,TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(11_in,TURN_SPEED);
  chassis.pid_wait();
}

///
// Turn Example
///
void turn_example() { // blue half
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_drive_set(-12.5_in, 45, true);
  chassis.pid_wait();
  chassis.pid_turn_set(30_deg,TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-23_in, 45, true);
  chassis.pid_wait();
  pros::delay(600);
  clamp_digi.set_value(true);
  pros::delay(800);
  
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
  pros::delay(100);
  intake.move(-127);
  chassis.pid_drive_set(21_in, 45, true);
  chassis.pid_wait();
  intake.move(127);
  pros::delay(100);
  intake.move(-127);
  chassis.pid_drive_set(-21_in, 45, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-12_in,45,true);
  //lift(11750);
  chassis.pid_turn_set(190_deg,TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(9.7_in,TURN_SPEED);
  chassis.pid_wait();
  // chassis.pid_wait();
  // chassis.pid_turn_set(180_deg, TURN_SPEED);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-30_in, 45, true);
  // chassis.pid_wait();
  // clamp_digi.set_value(false);
  // pros::delay(700);
  // chassis.pid_drive_set(6_in, 45, true);
  // chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() { // rush
  //flippe
  chassis.pid_drive_set(54_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .
