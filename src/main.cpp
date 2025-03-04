#include "main.h" // IWYU pragma: keep
#include "../includeB/robot-config.hpp"
#include "../includeB/userControlTools.hpp"
#include "../includeB/autonPaths.hpp"

	void on_center_button() {
		static bool pressed = false;
		pressed = !pressed;
		if (pressed) {
			pros::lcd::set_text(2, "I was pressed!");
		} else {
			pros::lcd::clear_line(2);
		}
	}

	void initialize() {
		controller.clear();
		pros::delay(51);
		pros::lcd::initialize();

		chainMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
		opticalSensor.set_led_pwm(100);

		chassis.calibrate(); // MUST BE LAST
		pros::delay(200);
	}
	

	void disabled() {
		/**
		 * Runs while the robot is in the disabled state of Field Management System or
		 * the VEX Competition Switch, following either autonomous or opcontrol. When
		 * the robot is enabled, this task will exit.
		 */
		pros::c::adi_digital_write('A', 0);
		pros::c::adi_digital_write('D', 0);
		pros::c::adi_digital_write('E', 0);
		
		}
		
	void competition_initialize() {
		while (pros::competition::is_disabled()) {
			if(autonSwitch.get_new_press()){
				controller.clear();
				pros::delay(100);
				autonState = static_cast<AutonState>((static_cast<int>(autonState) + 1) % static_cast<int>(AutonState::NUM_STATES)); // cycle between all 4 states dynamically
			}

			autonStateStr = autonStateNames[static_cast<int>(autonState)];
			controller.set_text(1, 6, autonStateStr);
			pros::delay(100);
		}
	}
		
	void autonomous() {
		if(autonState == AutonState::BLUE_NEG){
			colorSort = false;
			pros::Task opticalSensorTask(opticalTask);
			blueNegative();
		}else if(autonState==AutonState::RED_NEG){
			pros::Task opticalSensorTask(opticalTask);
			colorSort = true;
			redNegative();
		}else if(autonState==AutonState::BLUE_POS){
			colorSort = false;
			bluePositive();
		}else if(autonState==AutonState::RED_POS){
			// colorSort = true;
			// pros::Task opticalSensorTask(opticalTask);
			redPositive();
		}
		else{}

		pros::delay(100);
	}

	void opcontrol() {
		pros::Task cycleScreen(updateScreen);
		pros::Task checkOverheat(tempMonitor);
		bool screenTaskRemoved = false;
		
		
		while (true) {
			if (overheatWarningActive && !screenTaskRemoved) {
				cycleScreen.remove();
				screenTaskRemoved = true; 
			}

			int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
			int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
	
			//Reg or Invert Driving
			if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)){
				invertDriveState = !invertDriveState;
			}
			(!invertDriveState)? chassis.tank(leftY, rightY): chassis.tank(-rightY,-leftY);

			//Screen States
			if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)){
				screenState = static_cast<ScreenState>((static_cast<int>(screenState) + 1) % static_cast<int>(ScreenState::NUM_STATES)); // cycle between all 4 states dynamically
				pros::lcd::print(0, "Screen State: %d", static_cast<int>(screenState));
			}

			//INTAKE
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
				intakeState = (intakeState == IntakeState::FORWARD) ? IntakeState::STOPPED : IntakeState::FORWARD; //switch between fwd & stop
			}
			if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
				intakeState = (intakeState == IntakeState::REVERSE) ? IntakeState::STOPPED : IntakeState::REVERSE; //switch between reverse & stop
				intakeZState = !intakeZState;
			}
			intakeUp.set_value(intakeZState);
			updateIntake();

			//CLAMP
			solenoidClamp.set_value(!controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1));

			//DOINKER
			if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
				doinkerState = !doinkerState;
			}
			doinker.set_value(doinkerState);

			//SCORING
			//Nested ternary operators (IDK IF WORKING)
			//Lambda function syntax: [capture local vars (parameters) -> return_type { function body };
			//() excute lambda
			controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) ? chainMotor.move(chainVoltageFWD) :
			controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) ? chainMotor.move(chainVoltageREV) :
			[]()->std::int32_t {return chainMotor.brake();}(); 


			pros::delay(25);
		}
	}