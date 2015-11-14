#include <Commands/Scheduler.h>
#include <Commands/ToteLifting/LiftToHeight.h>
#include <Commands/ToteLifting/LiftToHeightVelocity.h>
#include <Encoder.h>
#include <LiveWindow/LiveWindow.h>
#include <OI.h>
#include <OmegaSupreme.h>
#include <RobotBase.h>
#include <RobotMap.h>
#include <stdio.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subsystems/ToteLifter.h>

OmegaSupreme::OmegaSupreme() {
	lw = NULL;
}

OmegaSupreme::~OmegaSupreme() {
}

void OmegaSupreme::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();

	CommandBase::oi->registerButtonListeners();

	SmartDashboard::PutNumber("P", TOTE_LIFTER_PID_P);
	SmartDashboard::PutNumber("I", TOTE_LIFTER_PID_I);
	SmartDashboard::PutNumber("D", TOTE_LIFTER_PID_D);

	SmartDashboard::PutData("40", new LiftToHeight(TOTE_LIFTER_40_HEIGHT));
	SmartDashboard::PutData("30", new LiftToHeight(TOTE_LIFTER_30_HEIGHT));
	SmartDashboard::PutData("20", new LiftToHeight(TOTE_LIFTER_20_HEIGHT));
	SmartDashboard::PutData("Floor",
			new LiftToHeight(TOTE_LIFTER_FLOOR_HEIGHT));

	SmartDashboard::PutData("Up", new LiftToHeightVelocity(.1));
	SmartDashboard::PutData("Down", new LiftToHeightVelocity(-.1));

	counter = 0;
}

void OmegaSupreme::AutonomousInit() {
	Scheduler::GetInstance()->RemoveAll();
	CommandBase::toteLifter->getEncoder()->Reset();
}

void OmegaSupreme::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void OmegaSupreme::TeleopInit() {
	//CommandBase::toteLifter->getEncoder()->Reset();
	Scheduler::GetInstance()->RemoveAll();
}

void OmegaSupreme::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	SmartDashboard::PutNumber("LifterEncoderInches",
			CommandBase::toteLifter->getPositionInches());
	counter++;
	if (counter > 15) {
		counter = 0;
		double p = SmartDashboard::GetNumber("P");
		double i = SmartDashboard::GetNumber("I");
		double d = SmartDashboard::GetNumber("D");

		CommandBase::toteLifter->setPID(p, i, d);
	}
	SmartDashboard::PutBoolean("LifterPIDEnabled",
			CommandBase::toteLifter->getPID()->IsEnabled());
	SmartDashboard::PutNumber("Error",
			CommandBase::toteLifter->getPID()->GetError());
	SmartDashboard::PutNumber("REAL P",
			CommandBase::toteLifter->getPID()->GetP());
	SmartDashboard::PutNumber("MotorValue",
			CommandBase::toteLifter->getLastOutputValue());

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
