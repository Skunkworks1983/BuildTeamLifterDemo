#include <CANTalon.h>
#include <Encoder.h>
#include <PIDController.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subsystems/ToteLifter.h>

ToteLifter::ToteLifter() :
		Subsystem("ToteLifter") {
	SAFE_INIT(TOTE_LIFTER_RIGHT_PORT,
			rightMotor = new CANTalon(TOTE_LIFTER_RIGHT_PORT););
	SAFE_INIT(TOTE_LIFTER_LEFT_PORT,
			leftMotor = new CANTalon(TOTE_LIFTER_LEFT_PORT););

	encoder = new Encoder(TOTE_LIFTER_ENCODER_PORTS);

	pid = new PIDController(TOTE_LIFTER_PID_P, TOTE_LIFTER_PID_I,
	TOTE_LIFTER_PID_D, this, this);
	pid->SetOutputRange(-.5, 1.0);
	pid->SetInputRange(0, 50);
	pid->Reset();
	//pid->SetPercentTolerance(.75);
	encoder->Reset();

	dontUseMagOnPID = true; //topInput->Get() && botInput->Get();
}

ToteLifter::~ToteLifter() {
	delete rightMotor;
	delete leftMotor;
	delete pid;
	delete encoder;
}

void ToteLifter::InitDefaultCommand() {
}

CANTalon *ToteLifter::getLeftMotor() {
	return leftMotor;
}

CANTalon *ToteLifter::getRightMotor() {
	return rightMotor;
}

double ToteLifter::getPosition() {
	return encoder->PIDGet();
}

Encoder *ToteLifter::getEncoder() {
	return encoder;
}

PIDController *ToteLifter::getPID() {
	return pid;
}

void ToteLifter::setPID(double p, double i, double d) {
	pid->SetPID(p, i, d);
}

void ToteLifter::enablePID(bool enable) {
	if (enable && !pid->IsEnabled()) {
		pid->Enable();
	}
	if (!enable && pid->IsEnabled()) {
		pid->Disable();
	}
}

float ToteLifter::getPositionInches() {
	return encoder->PIDGet() / TOTE_LIFTER_TICKS_PER_INCH;
}

void ToteLifter::setMotorSpeed(double speed) {
	if (speed < -1) {
		speed = -1;
	} else if (speed > 1) {
		speed = 1;
	}

	enablePID(false);
	leftMotor->Set(speed);
	rightMotor->Set(-speed);
}

void ToteLifter::setSetPoints(double setPoint) {
	if (setPoint >= 0) {
		pid->SetSetpoint(setPoint);
	}
}

bool ToteLifter::closeEnough(float destination) {
	bool close = encoder->Get() < destination + TOTE_LIFTER_TOLERANCE
			&& encoder->Get() > destination - TOTE_LIFTER_TOLERANCE;
	SmartDashboard::PutBoolean("closeEnough", close);
	return false;
	//return close;
}

double ToteLifter::getLastOutputValue(){
	return lastOutput;
}

void ToteLifter::PIDWrite(float f) {
	leftMotor->Set(-f);
	rightMotor->Set(f);
	lastOutput = f;
}

double ToteLifter::PIDGet() {
	return getPositionInches();
	//return encoder->PIDGet();
}
