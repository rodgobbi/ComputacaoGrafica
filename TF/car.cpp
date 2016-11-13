#include "classlib.h"

Car::Car() {
	visible = true;
	X = 0;
	Y = 0;
	Z = 0;
	XYAngle = 0;
	XZAngle = 0;
}
void Car::setGunXYAngle(GLfloat pAngle) {
	if (pAngle > 45)
		gunXYAngle = 45;
	else if (pAngle < -45)
		gunXYAngle = -45;
	else
		gunXYAngle = pAngle;
}
GLfloat Car::getDegreeGunXYAngle() {
	return gunXYAngle;
}
void Car::incGunXYAngle(GLfloat pAngle) {
	if ((gunXYAngle + pAngle) > 45)
		gunXYAngle = 45;
	else if ((gunXYAngle + pAngle) < -45)
		gunXYAngle = -45;
	else
		gunXYAngle += pAngle;
}
void Car::setGunXZAngle(GLfloat pAngle) {
	if (pAngle > 45)
		gunXZAngle = 45;
	else if (pAngle < 0)
		gunXZAngle = 0;
	else
		gunXZAngle = pAngle;
}
GLfloat Car::getDegreeGunXZAngle() {
	return gunXZAngle;
}
void Car::incGunXZAngle(GLfloat pAngle) {
	if ((gunXZAngle + pAngle) > 45)
		gunXZAngle = 45;
	else if ((gunXZAngle + pAngle) < 0)
		gunXZAngle = 0;
	else
		gunXZAngle += pAngle;
}
void Car::setRadius(GLfloat pRadius) {
	radius = pRadius;
	ZLength = pRadius/3;
	body.setXLength(pRadius*1.4);
	body.setYLength(pRadius/1.4);
	body.setZLength(pRadius/3);
	hub.setXLength(pRadius/6);
	hub.setRadius(pRadius/16);
	wheel.setXLength(pRadius/4);
	wheel.setRadius(pRadius/2 - pRadius/3.2);
	gun.setXLength(pRadius*0.3);
	gun.setRadius(pRadius/20);
}
void Car::setSteeringAngle(GLfloat pAngle) {
	if (pAngle > 45)
		steeringAngle = 45;
	else if (pAngle < -45)
		steeringAngle = -45;
	else
		steeringAngle = pAngle;
}
GLfloat Car::getDegreeSteeringAngle() {
	return steeringAngle;
}

void Car::setZLength(GLfloat pW) {
	ZLength = pW;
}

GLfloat Car::getZLength() {
	return ZLength;
}
