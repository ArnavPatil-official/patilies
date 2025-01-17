#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

//int iP,frP,mfP,brP,flP,mlP,blP,oP;

// int iP,frP,mrP,brP,flP,mlP,blP,oP,imuP;
// double wD, rpm;
// flP = 3;
// mlP = 5;
// blP = 4;
// frP = 7;
// mrP = 9;
// brP = 10;
// imuP = 8;
// wD = 2.75;
// rpm = 450; 
// Chassis constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {-15, -10, -6},     // Left Chassis Ports (negative port will reverse it!)
    {9, 8, 3},  // Right Chassis Ports (negative port will reverse it!)
    21,      // IMU Port
    2.75,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    450);   // Wheel RPM

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
 void saketh_nandam(int move_val) {
  wall_stake_mech_2.move(move_val);
  wall_stake_mech_1.move(-1*move_val);
}
void stop_saketh_nandam() {
  wall_stake_mech_2.brake();
  wall_stake_mech_1.brake();
}
bool intake_running = false;
const double intake_torque_threshold = 9.8;
void intake_check(void * param) {
  while (intake_running) {
      if (intake.get_torque() > intake_torque_threshold) {
        intake.brake();
    }
    pros::delay(10);
  }
}
double target_rotation;
void set_stake(int input) {
  wall_stake_mech_1.move(input);
}
const int numStates = 3;
//make sure these are in centidegrees (1 degree = 100 centidegrees)
int states[numStates] = {0, 300, 2000};
int currState = 0;
int target = 0;

void nextState() {
    currState += 1;
    if (currState == numStates) {
        currState = 0;
    }
    target = states[currState];
}

void liftControl() {
    double kp = 0.5;
    double error = target - rotation_sensor.get_position();
    double velocity = kp * error;
    wall_stake_mech_1.move(velocity);
}
// ez::PID stakePID{0.05, 0, 0, 0, "Stake"};
// void stake_task() {
//   pros::delay(2000);  // Set EZ-Template calibrate before this function starts running
//   while (true) {
//     set_stake(stakePID.compute(rotation_sensor.get_angle()));
//     pros::delay(ez::util::DELAY_TIME);
//  }
// }
  // Create the task, this will cause the function to start running
void initialize() {
  
  // Print our branding over your terminal :D
  ez::ez_template_print();
  wall_stake_mech_1.tare_position();
  pros::Task liftControlTask([]{
        while (true) {
            liftControl();
            pros::delay(10);
        }
    });
  // rotation_sensor.set_position(0);
  // pros::Task stake_task1(stake_task);
  // stakePID.target_set(0);
  // stakePID.exit_condition_set(80, 50, 300, 150, 500, 500);
  pros::delay(500);  // Stop the user from doing anything while legacy ports configure
  pros::motor_brake_mode_e_t lady_brown_brake = MOTOR_BRAKE_BRAKE;
  wall_stake_mech_1.set_brake_mode(lady_brown_brake);
  wall_stake_mech_2.set_brake_mode(lady_brown_brake);
  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(false);  // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(2);    // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(0, 0);     // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  // Set the drive to your own constants from autons.cpp!
  default_constants();
  //pros::task::create(intake_check, nullptr);

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
      Auton("skills.", skills),
      Auton("blue awp.", blue_awp),
      Auton("red awp. ", red_awp),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency

  skills(); 
  //red_awp();
  // red_awp();
}



bool clampstate = false;
bool flipperstate = false;


double setMech = 360;
double scoreMech = 3000;
double downMech = 0;

bool stakeCount = false;
void flip(bool example) {
  example = !example;
}
int stakeCounter = 0;

void opcontrol() {
  
  // This is preference to what you like to drive on
  pros::motor_brake_mode_e_t driver_preference_brake = MOTOR_BRAKE_COAST;
  intake.set_brake_mode(driver_preference_brake);
  chassis.drive_brake_set(driver_preference_brake);
 // wall_stake_mech_1.move_absolute(55,100);
  pros::delay(550);
  //rotationSet = true;
  while (true) {
    // PID Tuner
    // After you find values that you're happy with, you'll have to set them in auton.cpp
    if (!pros::competition::is_connected()) {
      // Enable / Disable PID Tuner
      //  When enabled:
      //  * use A and Y to increment / decrement the constants
      //  * use the arrow keys to navigate the constants
      if (master.get_digital_new_press(DIGITAL_X))
        chassis.pid_tuner_toggle();

      // Trigger the selected autonomous routine
      if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
        autonomous();
        chassis.drive_brake_set(driver_preference_brake);
      }

      chassis.pid_tuner_iterate();  // Allow PID Tuner to iterate
    }

    chassis.opcontrol_tank();  // Tank control
  
   

    if (master.get_digital(DIGITAL_R2)) {
        intake.move(-127);
      //  intake_running = true;
      }
    else if (master.get_digital(DIGITAL_R1)) {
      intake.move(127);
      //stakePID.target_set(-5/100);
      //wall_stake_mech_1.move_absolute(-45,100);
      stakeCounter = 0;
      //intake_running = true;
    }
    else {
      //intake_running = false;
      intake.move(0);
    }
      /*
    press and release for clamp l2
    l1 lady brown up w rotation sensor (code later)
    press it once to move lady brown to position and
     then press it agian to make go forward (score)
     outtake to lady brown down  - use rotaton sensr
    */
    // 41 is set
    // 260 is score
    // if (master.get_digital_new_press(DIGITAL_L1)) {
    //   if (stakeCounter == 0) {
    //     //stakePID.target_set(15/100);
    //     master.print(0, 0, "hello %d", rotation_sensor.get_angle());
    //     wall_stake_mech_1.move_absolute(-245,100);
    //     stakeCounter++;
    //   }
    //   else if (stakeCounter == 1) {
    //     //wall_stake_mech_1.move(-127);
    //     wall_stake_mech_1.move_absolute(-590,100);
    //     stakeCounter++;
    //   }
    //   else {
    //     wall_stake_mech_1.move_absolute(-1050,100);
    //     stakeCounter = 0;
    //   }
    while (true) {
	   if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
			nextState();
		}
      // wall_stake_mech_1.move(127);
      // if (fabs(wall_stake_mech_1.get_position()-41) > 2) {
      //   wall_stake_mech_1.brake();
      // }
    }
    
    if (master.get_digital_new_press(DIGITAL_UP)) {
      wall_stake_mech_1.move_absolute(-520,100);
    }
    if (master.get_digital_new_press(DIGITAL_L2)) {
      clampstate = !clampstate;
      clamp_digi.set_value(clampstate);
    }
    // if (master.get_digital_new_press(DIGITAL_L1)) {
    //   flipperstate = !flipperstate;
    //   henry_wo.set_value(flipperstate);
    // }

    // if (master.get_digital(DIGITAL_X)) {
    //   saketh_nandam(127);
    // } else if (master.get_digital(DIGITAL_Y)) {
    //   saketh_nandam(-127);
    // } else {
    //   stop_saketh_nandam();
    // }
    // pros::screen::print(pros::TEXT_LARGE, 3, "CTESPN");
    // master.print(0, 0, "Don't be saketh nandam");
    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}  

// chassis.opcontrol_arcade_standard(ez::SPLIT);   // Standard split arcade
    // chassis.opcontrol_arcade_standard(ez::SINGLE);  // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT);    // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE);   // Flipped single arcade
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

 /*
 henry_wo is the function that toggles pistons
 safwaan_majid is the variable that keeps track of the state of the piston
 kavinjit_sandhu is the piston that is being toggled
 parthiv_maddipatla is the variable that keeps track of the state of the piston in the function
 saketh_nandam is the lady brown mech
 */
//  void henry_wo(pros::ADIDigitalOut kavinjit_sandhu, bool parthiv_maddipatla) {
//   parthiv_maddipatla = !parthiv_maddipatla;
//   kavinjit_sandhu.set_value(parthiv_maddipatla);
//  }
//  bool henry_wo(bool parthiv_maddipatla) {
//   parthiv_maddipatla = !parthiv_maddipatla;
//   return parthiv_maddipatla;
//  }
 // Constants for interference detection
// const double PARTHIVS_CURRENT_THRESHOLD = 2.5; // Adjust this value based on testing
// const double SAKETH_EFFICIENCY_THRESHOLD = 50.0; // Adjust this value based on testing
// bool intake_running = false;
// const double intake_torque_threshold = 9.8;
// void intake_check(void * param) {
//   while (intake_running) {
//       if (intake.get_torque() > intake_torque_threshold) {
//         intake.brake();
//     }
//     pros::delay(10);
//   }
// }
