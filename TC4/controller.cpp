#include "classlib.h"

void Controller::setCarControlled(Car* pCarAddress) {
	carControlled = pCarAddress;
}

Car* Controller::getCar() {
	return carControlled;
}