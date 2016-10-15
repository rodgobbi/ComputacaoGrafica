#include "enginelib.h"

bool CirclesColliding (Circle pCircle1, Circle pCircle2) {
	GLfloat lDeltaX = pCircle1.getX() - pCircle2.getX();
	GLfloat lDeltaY = pCircle1.getY() - pCircle2.getY();
	GLfloat lRadiusSum = pCircle1.getRadius() + pCircle2.getRadius();
	return (lRadiusSum > sqrt(lDeltaX*lDeltaX + lDeltaY*lDeltaY));
}

bool CirclesColliding (Circle pCircle1, list<Circle> pCirclesList) {
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
void MoveShots(list<Circle> gShotsList, GLdouble timeDiff , GLdouble pSpeed) {
	for (list<Circle>::iterator it = gShotsList.begin(); it != gShotsList.end(); it++)
		*it = MoveObject(*it, timeDiff, pSpeed);
	// Destruir objetos nessa lista que após movidos estão fora da janela
}
Car MoveCar(Car pCar, GLdouble timeDiff , GLdouble pSpeed ) {
	if (gKeyboardStatus[(int)('w')] and !gKeyboardStatus[(int)('s')])
		return MoveObject(pCar, timeDiff, pSpeed);
	else if (gKeyboardStatus[(int)('s')] and !gKeyboardStatus[(int)('w')])
		return MoveObject(pCar, timeDiff, -pSpeed);
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