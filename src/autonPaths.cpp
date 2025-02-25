#include "main.h"
#include "liblvgl/llemu.hpp"
#include "../includeB/robot-config.hpp"
#include "../includeB/autonPaths.hpp"

void blueNegative(){
    pros::lcd::print(3, "%s", "BLUE NEG");
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