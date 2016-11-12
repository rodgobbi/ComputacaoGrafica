#include "classlib.h"

Car::Car() {
	visible = true;
	X = 0;
	Y = 0;
	Z = 0;
	XYAngle = 0;
	XZAngle = 0;
}
void Car::setGunXYAngle(GLfloat pAngleDirection) {
	if (pAngleDirection > 45)
		gunXYAngle = 45;
	else if (pAngleDirection < -45)
		gunXYAngle = -45;
	else
		gunXYAngle = pAngleDirection;
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
