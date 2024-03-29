#include <Commands/ToteLifting/LiftToHeight.h>
#include <Encoder.h>
#include <PIDController.h>
#include <RobotMap.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subsystems/ToteLifter.h>

LiftToHeight::LiftToHeight(double destination) :
		CommandBase("LiftToHeight") {
	Requires(toteLifter);
	this->initial = destination;
	this->destination = destination;
}

// Called just before this Command runs the first time
void LiftToHeight::Initialize() {
	destination = initial;

	toteLifter->setSetPoints(destination);
	toteLifter->enablePID(true);
	SmartDashboard::PutNumber("destination", destination);
}

// Called repeatedly when this Command is scheduled to run
void LiftToHeight::Execute() {
	//Nothing?
	/*if (destination == TOTE_LIFTER_FLOOR_HEIGHT
			&& toteLifter->closeEnough(destination)) {
		toteLifter->enablePID(false);
	}	//TODO: remove this useless garbage
	*/
}

// Make this return true when this Command no longer needs to run execute()
bool LiftToHeight::IsFinished() {
	//don't end when at destination because PID needs to hold the totes up until there is a tote underneath
	return false;
	//return false;
}

// Called once after isFinished returns true
void LiftToHeight::End() {
	//toteLifterino->getPID()->Disable();
	toteLifter->setSetPoints(toteLifter->getPositionInches());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftToHeight::Interrupted() {
	End();
}
