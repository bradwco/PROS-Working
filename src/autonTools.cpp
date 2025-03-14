#include "main.h" // IWYU pragma: keep
#include "../includeB/autonTools.hpp"
#include "../includeB/robot-config.hpp"

ColorSort colorSort = ColorSort::BLUE; //Sort BLUE by Default
const char* colors[] = {"BLUE", "RED"};

std::string autonStateStr = "DEFAULT";
double blueTargetHue = 0;
double redTargetHue = 0;

AutonState autonState = AutonState::SKILLS; //Skills by Default
const char* autonStateNames[] = {"BLUE NEG", "RED NEG", "BLUE POS", "RED POS", "SKILLS"};

void opticalTask(void) {
    bool detectedBlue = false;
    bool detectedRed = false;
    opticalSensor.set_led_pwm(100);
    while (true) {

        if (opticalSensor.get_hue() >= blueTargetHue) {
            detectedBlue = true;  // Blue object detected
        } 
        if (opticalSensor.get_hue() <= redTargetHue) {
            detectedRed = true;   // Red object detected
        }

        if (colorSort==ColorSort::BLUE && detectedBlue) {
                pros::delay(110);
                chainMotor.move(chainVoltageREV);
                pros::delay(200);
                chainMotor.move(chainVoltageFWD);
                detectedBlue = false;  
        } else if (detectedRed){
                pros::delay(110);
                chainMotor.move(chainVoltageREV);
                pros::delay(200);
                chainMotor.move(chainVoltageFWD);
                detectedRed = false;  
        }
        pros::delay(20);  
    }
}

