#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "liblvgl/llemu.hpp"
#include "../includeB/robot-config.hpp"
#include "pros/motors.h"
#include "../includeB/autonPaths.hpp"
#include <cmath>

void blueNegative() {
    pros::lcd::print(3, "%s", "BLUE NEG");
    chassis.setPose(tileSize*2-xOffset,tileSize-yOffset, 0);
    doinker.set_value(true);

    chassis.moveToPose(tileSize*2.4,tileSize*2.2, 0,2500);
    chassis.waitUntilDone();

    chassis.swingToHeading(70, lemlib::DriveSide::RIGHT,1500);
    chassis.waitUntilDone();

    chassis.moveToPose(tileSize*1.5,tileSize*1.4, 50,3000, {.forwards=false});
    chassis.waitUntilDone();

    chassis.turnToHeading(180,1500);
    chassis.waitUntilDone();

    doinker.set_value(false);
    pros::delay(300);

    //PASTED CODE BELOW

    
    chassis.moveToPose(tileSize*2, tileSize-4, 270, 3500, {.forwards=false, .maxSpeed=70});
    chassis.moveToPose(tileSize*3, tileSize-4, 270, 4000, {.forwards=false, .maxSpeed=30, .minSpeed=1, .earlyExitRange=1});
    chassis.waitUntilDone();
    chassis.setPose(tileSize*3, tileSize-4, 270);

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

    chassis.moveToPose(tileSize-5, tileSize-3, 270, 3500);
    chassis.waitUntilDone();

    chassis.moveToPose(xOffset+2+5, tileSize-3, 270, 3500);
    chassis.waitUntilDone();

    chassis.moveToPose(tileSize-xOffset-3+5, tileSize-3, 270, 2000, {.forwards = false});
    chassis.waitUntilDone();

    chassis.turnToHeading(0,2000); 
    
    chassis.moveToPose(tileSize-xOffset-3+5, tileSize*2+5, 0, 4000);
    chassis.waitUntilDone();

    chassis.moveToPose(tileSize-xOffset-3+5, tileSize*3-yOffset-4, 0, 4000);
    chassis.waitUntilDone();

    chassis.moveToPoint(0,0,4000,{.forwards=false, .maxSpeed=50});
    chassis.waitUntilDone();
    

}

void redNegative(){
    pros::lcd::print(3, "%s", "RED NEG");
    chassis.setPose(tileSize*2-xOffset-2,tileSize-yOffset+1.55, 270);
    chassis.moveToPose(tileSize*3, tileSize, 270, 3500, {.forwards=false, .maxSpeed=60, .minSpeed=1, .earlyExitRange=1});
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

    chassis.moveToPoint(tileSize,tileSize,4000);
    chassis.waitUntilDone();

    chassis.moveToPoint(tileSize*6,2,4000,{.forwards=false, .maxSpeed=70});
    chassis.waitUntilDone();
    
}

void bluePositive(){
    pros::lcd::print(3, "%s", "BLUE POS");
    pros::Task opticalSensorTask(opticalTask);
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
    
}

void redPositive(){
    pros::lcd::print(3, "%s", "RED POS");

    chassis.setPose(tileSize*5,0+yOffset, 0);

    intakeMotor.move(127);
    chassis.moveToPose(tileSize*5, tileSize+2, 0, 3000);
    chassis.waitUntilDone();
    chassis.moveToPose(tileSize*4, tileSize, 135+90, 2000);
    chassis.waitUntilDone();
    chassis.moveToPose(tileSize*5, tileSize*2-3, 135+90, 3000, {.forwards=false, .maxSpeed=30});
    chassis.waitUntilDone();
    solenoidClamp.set_value(true);

    
}
//Add skills
void skills(){
    pros::lcd::print(3, "%s", "SKILLS");

    chassis.setPose(tileSize*2-xOffset,tileSize-yOffset, 180);

    //Clamp Stake
    chassis.moveToPose(tileSize-2, tileSize*2, 140, 2000,  {.forwards=false, .maxSpeed=40, .minSpeed=2, .earlyExitRange=1});
    chassis.waitUntilDone();
    solenoidClamp.set_value(true);
    pros::delay(500);

    //First donut
    intakeMotor.move(127);
    chainMotor.move(chainVoltageFWD);
    chassis.turnToHeading(90,2000);
    chassis.waitUntilDone();
    chassis.moveToPose(tileSize*2, tileSize*2, 90, 2500);
    chassis.waitUntilDone();
    pros::delay(250);

    //Second donut
    chassis.turnToHeading(225,2000);
    chassis.waitUntilDone();
    chassis.moveToPose(tileSize, tileSize, 225, 2000);
    chassis.waitUntilDone();

    //Third donut and out
    chassis.moveToPose(0, 0, 225, 3000, {.maxSpeed=50});
    chassis.waitUntilDone();
    chassis.moveToPose(tileSize, tileSize, 225, 3000, {.forwards=false, .maxSpeed=50});
    chassis.waitUntilDone();

    //Corner
    chassis.turnToHeading(45,2000);
    chassis.waitUntilDone();
    chassis.moveToPose(0, 0, 45, 1500, {.forwards=false, .maxSpeed=40});
    chassis.waitUntilDone();
    solenoidClamp.set_value(false);

    //Middle Donuts
    chainMotor.move(0);
    chassis.moveToPose(tileSize-2, tileSize*3, 0, 3000);
    chassis.waitUntilDone();

    //Stake
    chassis.turnToHeading(225, 1500);
    chassis.moveToPose(tileSize*2+5, tileSize*4+5, 225, 4500, {.forwards=false, .maxSpeed=70, .minSpeed=2, .earlyExitRange=1});
    chassis.waitUntilDone();
    solenoidClamp.set_value(true);
    pros::delay(500);
    chainMotor.move(chainVoltageFWD);

    //2.1 Donut
    chassis.moveToPose(tileSize/2, tileSize*4, 270, 3000);
    chassis.waitUntilDone();

    //2.2 Donut
    chassis.moveToPose(tileSize/2, tileSize*5+5, 0, 3000);
    chassis.waitUntilDone();
    chassis.moveToPose(tileSize/2, tileSize*5, 0, 3000, {.forwards=false});
    chassis.waitUntilDone();

    //Corner + Blue Donut Reject
    chassis.turnToHeading(315, 1500);
    chassis.waitUntilDone();
    intakeUp.set_value(true);
    chassis.moveToPose(-10, tileSize*6, 315, 3000, {.maxSpeed=50});
    chassis.waitUntilDone();
    
    intakeUp.set_value(false);
    left_motor_group.move(-50);
    right_motor_group.move(-50);
    pros::delay(500);
    left_motor_group.move(0);
    right_motor_group.move(0);
    intakeMotor.move(-127);
    pros::delay(500);
    intakeMotor.move(127);
    pros::delay(500);

    //Red Corner Donut
    chassis.moveToPose(-10, tileSize*6, 315, 3000, {.maxSpeed=50});
    chassis.waitUntilDone();
    left_motor_group.move(-50);
    right_motor_group.move(-50);
    pros::delay(500);
    left_motor_group.move(0);
    right_motor_group.move(0);
    chassis.turnToHeading(135, 1500);
    chassis.moveToPose(-10, tileSize*6, 135, 3000, {.forwards=false, .maxSpeed=50});
    chassis.waitUntilDone();

    //Leave
    solenoidClamp.set_value(false);
    left_motor_group.move(50);
    right_motor_group.move(50);
    pros::delay(500);
    left_motor_group.move(0);
    right_motor_group.move(0);
    intakeMotor.move(0);
    chainMotor.move(0);



}