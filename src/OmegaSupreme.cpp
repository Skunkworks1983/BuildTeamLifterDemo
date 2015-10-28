#include <CommandBase.h>
#include <Commands/Scheduler.h>
#include <Encoder.h>
#include <LiveWindow/LiveWindow.h>
#include <OI.h>
#include <OmegaSupreme.h>
#include <RobotBase.h>
#include <stdio.h>
#include <Subsystems/ToteLifter.h>
#include "WPILib.h"

OmegaSupreme::OmegaSupreme() {
	lw = NULL;
}

OmegaSupreme::~OmegaSupreme() {
}

void OmegaSupreme::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();

	CommandBase::oi->registerButtonListeners();
}

void OmegaSupreme::AutonomousInit() {
	Scheduler::GetInstance()->RemoveAll();
	CommandBase::toteLifter->getEncoder()->Reset();
}

void OmegaSupreme::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void OmegaSupreme::TeleopInit() {
	CommandBase::toteLifter->getEncoder()->Reset();
	Scheduler::GetInstance()->RemoveAll();
}

void OmegaSupreme::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void OmegaSupreme::DisabledInit() {
	Scheduler::GetInstance()->RemoveAll();
}

void OmegaSupreme::TestInit() {
	Scheduler::GetInstance()->RemoveAll();
}

void OmegaSupreme::TestPeriodic() {
	Scheduler::GetInstance()->Run();
	lw->Run();
}

START_ROBOT_CLASS(OmegaSupreme);
