#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include "utilities/AnalogRangeIOButton.h"

class OI {
public:
	Joystick *joystickLeft;
	Joystick *joystickRight;
	Joystick *op;

	// How many buttons does a man need?

	JoystickButton *highPos;
	JoystickButton *midPos;
	JoystickButton *lowPos;
	JoystickButton *floorPos;

	JoystickButton *scoreOverride;
	JoystickButton *toteLifterUp;
	JoystickButton *toteLifterDown;
	JoystickButton *zeroLifter;

	JoystickButton *toteLifterUpDriver;
	JoystickButton *toteLifterDownDriver;

	AnalogRangeIOButton *score;

	OI();
	~OI();
	Joystick *getJoystickLeft();
	Joystick *getJoystickRight();
	Joystick *getJoystickOperator();
	double getAnalogValue(int input);
	bool getUnactuate();
	void registerButtonListeners();
	//bool isJoystickButtonPressed(bool isLeft, int val);
	void createButton(std::string key, Button *b, Command *c);
	void createSwitch(std::string key, Button *b, Command *on, Command *off);
};

#endif
