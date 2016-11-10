#include "classlib.h"

void Controller::setCarControlled(Car* pCarAddress) {
	carControlled = pCarAddress;
	turnLeft = true;
	foward = true;
	turning = false;
}

Car* Controller::getCar() {
	return carControlled;
}