#include "main.h" // IWYU pragma: keep
#include "pros/adi.h"
#include "../includeB/robot-config.hpp"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::MotorGroup left_motor_group({-15,16,-17,18}, pros::MotorGearset::blue);
pros::MotorGroup right_motor_group({11,-12,13,-14}, pros::MotorGearset::blue);
pros::Motor intakeMotor(-10, pros::MotorGearset::blue);
pros::Motor chainMotor(-9, pros::MotorGearset::blue);
pros::adi::DigitalOut solenoidClamp('A', LOW);
pros::adi::DigitalIn autonSwitch('D');
pros::adi::DigitalOut doinker('C', LOW);
pros::adi::DigitalOut intakeUp('E', LOW);
pros::Optical opticalSensor(8);

pros::Imu imu(1);
pros::Rotation vertical_encoderL(-20);
pros::Rotation vertical_encoderR(19);
pros::Rotation horizontal_encoder(-4);

lemlib::Drivetrain drivetrain(&left_motor_group,
    &right_motor_group, 
    12.375, 
    lemlib::Omniwheel::NEW_325, 
    600, 
    2
);

lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_2, 0);
lemlib::TrackingWheel vertical_tracking_wheelL(&vertical_encoderL, lemlib::Omniwheel::NEW_2, -2.546);
lemlib::TrackingWheel vertical_tracking_wheelR(&vertical_encoderR, lemlib::Omniwheel::NEW_2, 2.546);

lemlib::OdomSensors sensors(
    &vertical_tracking_wheelR, 
    nullptr, //Put in left one in future (if fixed)
    &horizontal_tracking_wheel, 
    nullptr, 
    &imu 
);

lemlib::ControllerSettings lateral_controller(10,
                                              0, 
                                              5, 
                                              3, // anti windup
                                              1, // in
                                              100, // ms
                                              3, // in
                                              500, // ms
                                              20 // max accel
);

lemlib::ControllerSettings angular_controller(2,
                                              0,
                                              12,
                                              0, // anti windup
                                              1, // in
                                              100, // ms
                                              3, // in
                                              500, // ms
                                              0 // max accel
);

lemlib::Chassis chassis(drivetrain, 
    lateral_controller, 
    angular_controller, 
    sensors
);

const double xOffset = 7.25;
const double yOffset = 7.5;
const double tileSize = 24;
const double intakeVoltage = 217;
const double chainVoltageFWD = 163;
const double chainVoltageREV = -217;
const double overHeatTemp = 140; //Farhenheit
bool overheatWarningActive = false; //used to disable the updateScreen
bool invertDriveState = false;
std::string autonStateStr = "DEFAULT";
bool doinkerState = false;
bool intakeZState = false;
bool colorSort = false; //TRUE IS SORT BLUE, FALSE IS SORT RED

void opticalTask(void) {
    while (true) {
        if(colorSort){
            if (opticalSensor.get_hue() >= 200) {  // Detect blue object (donut)
                pros::delay(40); 
                chainMotor.move(-127); 
                pros::delay(110);  
                chainMotor.move(127);  
            }
        }else{
            if (opticalSensor.get_hue() <= 25) {  // Detect red object (donut)
                pros::delay(40); 
                chainMotor.move(-127); 
                pros::delay(110);  
                chainMotor.move(127);  
            }
        }
        pros::delay(10);  // Prevent CPU overload
    }
}
