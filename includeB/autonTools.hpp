#ifndef AUTON_TOOLS_HPP
#define AUTON_TOOLS_HPP
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "main.h" // IWYU pragma: keep

// Color Sorting Modes
enum class ColorSort {BLUE, RED}; 
extern ColorSort colorSort;
extern const char* colors[];

extern std::string autonStateStr;
extern double blueTargetHue;
extern double redTargetHue;

// Auton States
enum class AutonState {BLUE_NEG, RED_NEG, BLUE_POS, RED_POS, SKILLS, NUM_STATES};
extern AutonState autonState;
extern const char* autonStateNames[];

//MSC Functions
extern void opticalTask(void);
#endif