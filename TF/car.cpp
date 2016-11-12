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
	body.setXLength(pRadius*1.4);
	body.setYLength(pRadius/1.8);
	hub.setXLength(pRadius/10);
	hub.setYLength(pRadius/4);
	wheel.setXLength(pRadius*0.4);
	wheel.setYLength(pRadius/4);
	wheelStripe.setXLength(pRadius*0.05);
	wheelStripe.setYLength(pRadius/4);
	gun.setXLength(pRadius*0.3);
	gun.setYLength(pRadius/10);
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
