#include "classlib.h"

Car::Car() {
	visible = true;
	X = 0;
	Y = 0;
	Z = 0;
	direction = 0;
	Zdirection = 0;
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
	wheelStripe.setWidth(pRadius*0.05);
	wheelStripe.setHeight(pRadius/4);
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
void Car::setWheelStripePosition(GLfloat pPercentage){
	if (pPercentage > 1)
		wheelStripePosition = 1;
	else if (pPercentage < 0)
		wheelStripePosition = 0;
	else
		wheelStripePosition = pPercentage;	
}
GLfloat Car::getWheelStripePosition() {
	return wheelStripePosition;
}
void Car::incWheelStripePosition(GLfloat pPercentage) {
	GLfloat lDecimal = fmod(pPercentage,1.0);
	if ( (wheelStripePosition + lDecimal) < 0.0)
		wheelStripePosition = 1 + (wheelStripePosition + lDecimal);
	else
		wheelStripePosition = fmod(wheelStripePosition + lDecimal, 1.0);
}
