#include "main.h"
#include "liblvgl/llemu.hpp"
#include "../includeB/robot-config.hpp"
#include "../includeB/autonPaths.hpp"

void blueNegative(){
    pros::lcd::print(3, "%s", "BLUE NEG");

    chassis.setPose(tileSize*4-xOffset,tileSize-yOffset,0);
    chassis.moveToPose(tileSize*4-xOffset, tileSize*2, 323, 1500, {.minSpeed=70, .earlyExitRange=10});
    chassis.waitUntilDone();
    chassis.cancelAllMotions();

    left_motor_group.move(20);
    right_motor_group.move(20);
    pros::delay(4000);
    left_motor_group.brake();
    right_motor_group.brake();

    left_motor_group.move(-100);
    right_motor_group.move(-100);
    pros::delay(500);
    left_motor_group.brake();
    right_motor_group.brake();

    chassis.moveToPose(tileSize*4-xOffset,tileSize-yOffset,0, 3000, {.forwards=false});
}

void redNegative(){
    pros::lcd::print(3, "%s", "RED NEG");
}

void bluePositive(){
    pros::lcd::print(3, "%s", "BLUE POS");
}

void redPositive(){
    pros::lcd::print(3, "%s", "RED POS");
}
//Add skills