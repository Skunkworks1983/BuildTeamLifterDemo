#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <Subsystems/ToteLifter.h>
#include <string>
#include "Commands/Command.h"
#include "OI.h"
#include "WPILib.h"

/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 */

class ToteLifter;

class CommandBase: public Command {
public:
	CommandBase(char const *name);
	CommandBase();
	~CommandBase();
	static void init();
	// Create a single static instance of all of your subsystems

	static ToteLifter *toteLifter;
	static OI *oi;
};

#endif

