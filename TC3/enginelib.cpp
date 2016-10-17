#include "enginelib.h"

bool CirclesColliding (Circle pCircle1, Circle pCircle2) {
	GLfloat lDeltaX = pCircle1.getX() - pCircle2.getX();
	GLfloat lDeltaY = pCircle1.getY() - pCircle2.getY();
	GLfloat lRadiusSum = pCircle1.getRadius() + pCircle2.getRadius();
	return (lRadiusSum > sqrt(lDeltaX*lDeltaX + lDeltaY*lDeltaY));
}

bool CirclesColliding (Circle pCircle1, list<Circle> &pCirclesList) {
	for (list<Circle>::iterator it = pCirclesList.begin(); it != pCirclesList.end(); it++)
		if ( CirclesColliding ( pCircle1, *it) )
			return true;
	return false;
}

bool CircleCovered(Circle pInnerCircle, Circle pOuterCircle) {
	GLfloat lDeltaX = pInnerCircle.getX() - pOuterCircle.getX();
	GLfloat lDeltaY = pInnerCircle.getY() - pOuterCircle.getY();
	GLfloat lMaximumDistance = pOuterCircle.getRadius() - pInnerCircle.getRadius();
	return (lMaximumDistance > sqrt(lDeltaX*lDeltaX + lDeltaY*lDeltaY));
}
template<class tObject>
tObject MoveObject(tObject pObject, GLdouble timeDiff , GLdouble pSpeed) {
	GLfloat lDirection = pObject.getRadianDirection();
	pObject.incX(pSpeed * timeDiff * cos(lDirection) );
	pObject.incY(pSpeed * timeDiff * sin(lDirection) );
	return pObject;
}
void MoveShots(list<Circle> &pShotsList, GLdouble timeDiff , GLdouble pSpeed, Circle pOuterCircle) {
	list<Circle>::iterator it = pShotsList.begin();
	while	(it != pShotsList.end()) {
		*it = MoveObject(*it, timeDiff, pSpeed);
		if ( PointOutOfWindow(*it, pOuterCircle) )
			it = pShotsList.erase(it);
		else
			it++;	
	}
}
Car MoveCar(Car pCar, GLdouble timeDiff , GLdouble pSpeed ) {
	if (gKeyboardStatus[(int)('w')] and !gKeyboardStatus[(int)('s')]){
		pCar.incWheelStripePosition(timeDiff * pSpeed/25);
		return MoveObject(pCar, timeDiff, pSpeed);
	}
	else if (gKeyboardStatus[(int)('s')] and !gKeyboardStatus[(int)('w')]){
		pCar.incWheelStripePosition(-timeDiff * pSpeed/25);
		return MoveObject(pCar, timeDiff, -pSpeed);
	}
	else
		return pCar;
}

Car RotateCar(Car pCar, GLdouble timeDiff , GLdouble pSpeed ) {
	if (gKeyboardStatus[(int)('w')] and !gKeyboardStatus[(int)('s')]) {
		if (gKeyboardStatus[(int)('a')] and !gKeyboardStatus[(int)('d')])
			pCar.incDirectionAngle(pSpeed * timeDiff);
		else if (gKeyboardStatus[(int)('d')] and !gKeyboardStatus[(int)('a')])
			pCar.incDirectionAngle(-pSpeed * timeDiff);
	}
	else if (gKeyboardStatus[(int)('s')] and !gKeyboardStatus[(int)('w')]) {
		if (gKeyboardStatus[(int)('a')] and !gKeyboardStatus[(int)('d')])
			pCar.incDirectionAngle(-pSpeed * timeDiff);
		else if (gKeyboardStatus[(int)('d')] and !gKeyboardStatus[(int)('a')])
			pCar.incDirectionAngle(pSpeed * timeDiff);
	}

	return pCar;
}
Car SteerCarWheels(Car pCar, GLdouble timeDiff , GLdouble pSpeed ) {
	if (gKeyboardStatus[(int)('a')] and !gKeyboardStatus[(int)('d')])
		pCar.setSteeringAngle(pSpeed * timeDiff * 10);
	else if (gKeyboardStatus[(int)('d')] and !gKeyboardStatus[(int)('a')])
		pCar.setSteeringAngle(-pSpeed * timeDiff * 10);
	else
		pCar.setSteeringAngle(0);

	return pCar;
}
Circle CarShot(Car pCar) {
	Circle lShot;
	lShot.setRadius(3);
	lShot.setRGB(1,1,0);
	lShot.setPosition(pCar.getX(),pCar.getY());
	lShot.setDirection(pCar.getDegreeDirection());
	lShot = MoveObject(lShot, 1, pCar.body.getWidth()/2);
	lShot.incDirectionAngle(pCar.getDegreeGunDirection());
	lShot = MoveObject(lShot, 1, pCar.gun.getWidth());
	return lShot;
}
bool PointOutOfWindow(Object pObject, Circle pOuterCircle) {
	if ( pObject.getX() <  (pOuterCircle.getX() - pOuterCircle.getRadius()))
		return true;
	if ( pObject.getX() > (pOuterCircle.getX() + pOuterCircle.getRadius()))
		return true;
	if ( pObject.getY() <  (pOuterCircle.getY() - pOuterCircle.getRadius()))
		return true;
	if ( pObject.getY() > (pOuterCircle.getY() + pOuterCircle.getRadius()))
		return true;
	return false;
}