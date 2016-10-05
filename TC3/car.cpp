#include "classlib.h"

Car::Car() {
	visible = true;
}

void Car::setDirection(GLfloat pAngleDirection) {
	direction = pAngleDirection;
}

GLfloat Car::getDirection() {
	return direction;
}

void Car::incAngleDirection(GLfloat pAngle) {
	direction = direction + pAngle;
}