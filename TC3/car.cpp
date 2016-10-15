#include "classlib.h"

Car::Car() {
	visible = true;
	X = 0;
	Y = 0;
}
void Car::setDirection(GLfloat pAngleDirection) {
	direction = fmod(pAngleDirection, 360.0);
}
GLfloat Car::getRadianDirection() {
	return direction * M_PI / 180;
}
GLfloat Car::getDegreeDirection() {
	return direction;
}
void Car::incDirectionAngle(GLfloat pAngle) {
	direction = fmod((direction + pAngle), 360.0);
}
void Car::setGunDirection(GLfloat pAngleDirection) {
	if (pAngleDirection > 45)
		gunDirection = 45;
	else if (pAngleDirection < -45)
		gunDirection = -45;
	else
		gunDirection = pAngleDirection;
}
GLfloat Car::getDegreeGunDirection() {
	return gunDirection;
}
void Car::incGunDirectionAngle(GLfloat pAngle) {
	if ((gunDirection + pAngle) > 45)
		gunDirection = 45;
	else if ((gunDirection + pAngle) < -45)
		gunDirection = -45;
	else
		gunDirection += pAngle;
}
void Car::setRadius(GLfloat pRadius) {
	radius = pRadius;
	body.setWidth(pRadius*1.4);
	body.setHeight(pRadius/1.8);
	hub.setWidth(pRadius/10);
	hub.setHeight(pRadius/4);
	wheel.setWidth(pRadius*0.4);
	wheel.setHeight(pRadius/4);
	gun.setWidth(pRadius*0.3);
	gun.setHeight(pRadius/10);
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