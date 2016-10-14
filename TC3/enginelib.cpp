#include "enginelib.h"

bool CirclesColliding (Circle pCircle1, Circle pCircle2) {
	GLfloat lDeltaX = pCircle1.getX() - pCircle2.getX();
	GLfloat lDeltaY = pCircle1.getY() - pCircle2.getY();
	GLfloat lRadiusSum = pCircle1.getRadius() + pCircle2.getRadius();
	return (lRadiusSum > sqrt(lDeltaX*lDeltaX + lDeltaY*lDeltaY));
}

bool CirclesColliding (Circle pCircle1, list<Circle> pCirclesList) {
	for (list<Circle>::iterator it = pCirclesList.begin(); it != pCirclesList.end(); it++)
		if ( CirclesColliding ( pCircle1, (Circle) *it) )
			return true;
	return false;
}

bool CircleCovered(Circle pInnerCircle, Circle pOuterCircle) {
	GLfloat lDeltaX = pInnerCircle.getX() - pOuterCircle.getX();
	GLfloat lDeltaY = pInnerCircle.getY() - pOuterCircle.getY();
	GLfloat lMaximumDistance = pOuterCircle.getRadius() - pInnerCircle.getRadius();
	return (lMaximumDistance > sqrt(lDeltaX*lDeltaX + lDeltaY*lDeltaY));
}

Car MoveCar(Car pCar, GLdouble timeDiff , GLdouble pSpeed ) {
	GLfloat lDirection = pCar.getDirection();
	if (gKeyboardStatus[(int)('w')]) {
		pCar.incX(pSpeed * timeDiff * cos(lDirection) );
		pCar.incY(pSpeed * timeDiff * sin(lDirection) );
	}
	if (gKeyboardStatus[(int)('s')]) {
		pCar.incX(-pSpeed * timeDiff * cos(lDirection) );
		pCar.incY(-pSpeed * timeDiff * sin(lDirection) );
	}
	return pCar;
}

Car RotateCar(Car pCar, GLdouble timeDiff , GLdouble pSpeed ) {
	if (gKeyboardStatus[(int)('a')])
		pCar.incAngleDirection(pSpeed * timeDiff * M_PI );

	if (gKeyboardStatus[(int)('d')])
		pCar.incAngleDirection(-pSpeed * timeDiff * M_PI);

	return pCar;
}
