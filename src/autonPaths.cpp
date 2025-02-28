#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "liblvgl/llemu.hpp"
#include "../includeB/robot-config.hpp"
#include "pros/motors.h"
#include "../includeB/autonPaths.hpp"

void blueNegative() {
    pros::lcd::print(3, "%s", "BLUE NEG");
    
}

void redNegative(){
    pros::lcd::print(3, "%s", "RED NEG");
}

void bluePositive(){
    pros::lcd::print(3, "%s", "BLUE POS");
    chainMotor.tare_position();
    chassis.setPose(tileSize*2-xOffset-2,tileSize-yOffset+1.55, 270);
    chassis.moveToPose(tileSize*3, tileSize, 270, 3000, {.forwards=false, .minSpeed=1, .earlyExitRange=1});
    chassis.waitUntilDone();

    solenoidClamp.set_value(true);
    pros::delay(1000);

    //CHAIN MOTOR MOVE 1 ROTATION
    chainMotor.move(127);
    while (chainMotor.get_position() < 1800) {
        pros::delay(10);
    }
    
    chassis.moveToPose(tileSize*2.25, tileSize, 270, 2000, {.minSpeed = 5 , .earlyExitRange = 5});
    chassis.waitUntilDone();
    chassis.turnToHeading(130, 2000, {.minSpeed = 5 , .earlyExitRange = 5});
    chassis.waitUntilDone();
    chainMotor.move(0);

    chainMotor.move(127);

    intakeMotor.move(127);

    chassis.moveToPose(tileSize*3, tileSize/2, 130, 2000, {.minSpeed = 10, .earlyExitRange = 10});
    chassis.waitUntilDone();
    chassis.moveToPose(tileSize*3-5, tileSize/2-5, 130, 1000, {.minSpeed = 10, .earlyExitRange = 5});
    chassis.waitUntilDone();

    chassis.swingToHeading(90, lemlib::DriveSide::LEFT, 2000, {.minSpeed = 5, .earlyExitRange = 10});
    chassis.waitUntilDone();

    chassis.moveToPose(tileSize*3.75, tileSize/2, 87, 3000);
    chassis.waitUntilDone();

    chassis.moveToPose(tileSize, tileSize-3, 270, 3500);
    chassis.waitUntilDone();

    chassis.moveToPose(xOffset+2, tileSize-3, 270, 3500);
    chassis.waitUntilDone();

    chassis.moveToPose(tileSize-xOffset, tileSize-3, 270, 2000, {.forwards = false});
    chassis.waitUntilDone();

    chassis.turnToHeading(0,2000); 
    
    chassis.moveToPose(tileSize-xOffset, tileSize*2+5, 0, 4000);
    chassis.waitUntilDone();

    chassis.moveToPose(tileSize-xOffset, tileSize*3-yOffset-4, 0, 4000);
    chassis.waitUntilDone();

    chassis.moveToPoint(0,0,4000,{.forwards=false, .maxSpeed=50});
    chassis.waitUntilDone();
    
    solenoidClamp.set_value(false);
    pros::delay(500);

    chassis.moveToPose(tileSize-xOffset, tileSize*3-yOffset-4, 0, 3000);
    chassis.waitUntilDone();
}

void redPositive(){
    pros::lcd::print(3, "%s", "RED POS");
}
//Add skills