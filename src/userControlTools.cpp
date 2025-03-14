#include "main.h" // IWYU pragma: keep
#include "../includeB/userControlTools.hpp"
#include "../includeB/robot-config.hpp"

//Global States
IntakeState intakeState = IntakeState::STOPPED; //stop it by default
ScreenState screenState = ScreenState::DRIVE_TEMPS;

//Mechanism Functions
void updateIntake(){
    switch(intakeState)
    {
    case IntakeState::FORWARD:
        intakeMotor.move(intakeVoltage);
        break;
    case IntakeState::REVERSE:
        intakeMotor.move(-intakeVoltage);
        break;
    case IntakeState::STOPPED:
    default:
        intakeMotor.brake();
    }
}
void displayDriveTemps(){
    std::vector<double> tempsL = left_motor_group.get_temperature_all();
    std::vector<double> tempsR = right_motor_group.get_temperature_all();

    for (size_t i = 0; i < tempsL.size(); i++) {
        tempsL[i] = (tempsL[i] * 9 / 5) + 32;
    }
    
    for (size_t i = 0; i < tempsR.size(); i++) {
        tempsR[i] = (tempsR[i] * 9 / 5) + 32;
    }
    controller.set_text(0, 2, "DRIVE TEMPS (F)");
    pros::delay(100);
    controller.print(1, 0, "L: %.0f %.0f %.0f %.0f", tempsL[0], tempsL[1], tempsL[2], tempsL[3]);
    pros::delay(51);
    controller.print(2, 0, "R: %.0f %.0f %.0f %.0f", tempsR[0], tempsR[1], tempsR[2], tempsR[3]);
    pros::delay(51);
}
void displayMechsTemps(){
    double motorChainTemp = chainMotor.get_temperature();
    double motorIntakeTemp = intakeMotor.get_temperature();

    motorChainTemp = (motorChainTemp * 9 / 5) + 32;
    motorIntakeTemp = (motorIntakeTemp * 9 / 5) + 32;

    controller.print(0,2,"MECHS TEMPS (F)");
    pros::delay(100);
    controller.print(1, 0, "Chain Temp: %.0f", motorChainTemp);
    pros::delay(51);
    controller.print(2, 0, "Intake Temp: %.0f", motorIntakeTemp);
    pros::delay(51);
}

void updateScreen(void){
    pros::delay(51);
    while(true){
        controller.clear();
        pros::delay(150);
        switch(screenState)
        {
            case ScreenState::MECHS_TEMPS:
                displayMechsTemps();
                break;
            case ScreenState::DRIVE_TEMPS:
            default:
                displayDriveTemps();
                break;
        }
        pros::delay(1000);
    }
}

void tempMonitor(void) {
    while (true) {
        std::vector<double> allTemps;
        std::vector<std::string> warnings;  
        overheatWarningActive = false;

        std::vector<double> leftTemps = left_motor_group.get_temperature_all();
        std::vector<double> rightTemps = right_motor_group.get_temperature_all();

        allTemps.insert(allTemps.end(), leftTemps.begin(), leftTemps.end());
        allTemps.insert(allTemps.end(), rightTemps.begin(), rightTemps.end());
        allTemps.push_back(intakeMotor.get_temperature());
        allTemps.push_back(chainMotor.get_temperature());

        for (size_t i = 0; i < allTemps.size(); i++) {
                allTemps[i] = (allTemps[i] * 9 / 5) + 32;
        }

        for (size_t i = 0; i < allTemps.size(); i++) {
            if (allTemps[i] >= overHeatTemp && allTemps[i]<=overHeatTemp+200) {
                overheatWarningActive = true;

                if (i < 4) {
                    warnings.push_back("LEFT OVERHEAT");
                } else if (i < 8) {
                    warnings.push_back("RIGHT OVERHEAT");
                } else if (i == 8) {
                    warnings.push_back("INTAKE OVERHEAT");
                } else if (i == 9) {
                    warnings.push_back("CHAIN OVERHEAT");
                }
            }
        }

        if (overheatWarningActive) {
            controller.rumble(".............");
            controller.clear();
            pros::delay(500);

            if (warnings.size() >= 3) {
                controller.clear();
                pros::delay(500);
                controller.print(0, 6, "WARNING");
                pros::delay(1000);
                controller.print(1, 1, "3+ OVERHEATING");
                pros::delay(1000);
                controller.print(2, 6, "WARNING");
                pros::delay(1000);
            } else {
                controller.clear();
                pros::delay(500);
                if (warnings.size() > 0) controller.print(0, 0, warnings[0].c_str());
                pros::delay(1000);
                if (warnings.size() > 1) controller.print(2, 0, warnings[1].c_str());
                pros::delay(1000);
            }
        }

        pros::delay(1000);  
    }
}
