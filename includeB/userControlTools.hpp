#ifndef USER_CONTROL_HPP
#define USER_CONTROL_HPP

//Global States/Classes
enum class IntakeState {FORWARD, REVERSE, STOPPED};
extern IntakeState intakeState;
enum class ScreenState {DRIVE_TEMPS, MECHS_TEMPS, DRIVE_CONNECTS, MECHS_CONNECTS, NUM_STATES}; //NUM_STATES auto detects states to be dynamic
extern ScreenState screenState;
enum class AutonState {BLUE_NEG, RED_NEG, BLUE_POS, RED_POS, SKILLS, NUM_STATES};
extern AutonState autonState;
extern const char* autonStateNames[];

//Mechanism Functions
extern void updateIntake();
extern void displayDriveTemps();
extern void displayMechsTemps();
extern void updateScreen(void); 
extern void tempMonitor(void);

#endif