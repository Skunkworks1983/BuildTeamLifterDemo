#include <Buttons/JoystickButton.h>
#include <Commands/Score.h>
#include <Commands/ToteLifting/LiftToHeight.h>
#include <Commands/ToteLifting/LiftToHeightVelocity.h>
#include <Commands/ToteLifting/PIDHoldLiftToHeightVelocity.h>
#include <Commands/ToteLifting/zeroing/ResetElevatorEncoder.h>
#include <Joystick.h>
#include <OI.h>
#include <RobotMap.h>
#include <string>

#define SAFE_BUTTON(name, cmd) {if (name!=NULL){cmd;}}
#define VIRTUAL_OI false
#define OPERATOR_PORT 2

OI::OI() {
	joystickLeft = new Joystick(0);

	// Tote stacking
	highPos = new JoystickButton(joystickLeft, 4);
	midPos = new JoystickButton(joystickLeft, 3);
	lowPos = new JoystickButton(joystickLeft, 2);
	floorPos = new JoystickButton(joystickLeft, 1);

	// Overrides
	toteLifterUp = new JoystickButton(joystickLeft, 5);
	toteLifterDown = new JoystickButton(joystickLeft, 6);
	zeroLifter = new JoystickButton(joystickLeft, 7);

	// Driver buttons
	toteLifterUpDriver = new JoystickButton(joystickLeft, 8);
	toteLifterDownDriver = new JoystickButton(joystickLeft, 9);
	scoreOverride = new JoystickButton(joystickLeft, 10);
}

OI::~OI() {
	delete joystickLeft;
	delete score;
	delete floorPos;
	delete toteLifterUp;
	delete toteLifterDown;
	delete zeroLifter;
	delete toteLifterUpDriver;
	delete toteLifterDownDriver;
}

Joystick *OI::getJoystickOperator() {
	return op;
}

Joystick *OI::getJoystickLeft() {
	return joystickLeft;
}

Joystick *OI::getJoystickRight() {
	return joystickRight;
}

double OI::getAnalogValue(int input) {
	//find input at port %input%
	//return analog value for that device
	return 0.0;
}

void OI::registerButtonListeners() {
	// Loading/stacking




	createButton("score", score, new Score());

	// Overrides
	createSwitch("lifter up override", toteLifterUp,
			new LiftToHeightVelocity(.5), new LiftToHeightVelocity(0)); // TODO sketchy
	createSwitch("lifter down override", toteLifterDown,
			new LiftToHeightVelocity(-.5), new LiftToHeightVelocity(0));
	createButton("zero lifter", zeroLifter, new ResetElevatorEncoder());

	// Special driver buttons
	SAFE_BUTTON(toteLifterUpDriver,
			toteLifterUpDriver->WhileHeld(new PIDHoldLiftToHeightVelocity(.75)));
	SAFE_BUTTON(toteLifterDownDriver,
			toteLifterDownDriver->WhileHeld(
					new PIDHoldLiftToHeightVelocity(-0.75)));
	createButton("Drive score override", scoreOverride, new Score());
}

void OI::createButton(std::string key, Button *b, Command *c) {
	SAFE_BUTTON(b, b->WhenPressed(c));
#if VIRTUAL_OI
	SmartDashboard::PutData(key, c);
#endif
}

void OI::createSwitch(std::string key, Button *b, Command *on, Command *off) {
	SAFE_BUTTON(b, b->WhenPressed(on));
	SAFE_BUTTON(b, b->WhenReleased(off));
#if VIRTUAL_OI
	SmartDashboard::PutData(key + " ON", on);
	SmartDashboard::PutData(key + " OFF", off);
#endif
}

/*bool OI::isJoystickButtonPressed(bool isLeft, int val) {
	if (isLeft) {
		return val > 0 && val < joystickLeft->GetButtonCount()
				&& joystickLeft->GetRawButton(val);
	} else {
		return val > 0 && val < joystickRight->GetButtonCount()
				&& joystickRight->GetRawButton(val);
	}
}*/

