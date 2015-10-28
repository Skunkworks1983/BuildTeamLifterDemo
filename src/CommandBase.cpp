#include <CommandBase.h>

// Initialize a single static instance of all of your subsystems to NULL
OI* CommandBase::oi = NULL;
ToteLifter* CommandBase::toteLifter = NULL;

CommandBase::CommandBase(char const *name) :
		Command(name) {
}

CommandBase::CommandBase() :
		Command() {
}

CommandBase::~CommandBase() {
	delete toteLifter;
	delete oi;
}

void CommandBase::init() {
	toteLifter = new ToteLifter();
	oi = new OI();
}
