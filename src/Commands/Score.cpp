#include <Commands/Score.h>
#include <Commands/ToteLifting/LiftToHeight.h>
#include <RobotMap.h>

Score::Score() {
	AddSequential(new LiftToHeight(TOTE_LIFTER_FLOOR_HEIGHT));
}
