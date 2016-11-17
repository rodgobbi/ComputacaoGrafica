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

bool CirclesColliding (Circle pCircle1, list<Car> &pCarsList) {
	for (list<Car>::iterator it = pCarsList.begin(); it != pCarsList.end(); it++)
		if ( CirclesColliding ( pCircle1, *it) )
			return true;
	return false;
}

bool ShotsColliding (Circle pCircle1, list<Car> &pCarsList) {
	for (list<Car>::iterator it = pCarsList.begin(); it != pCarsList.end(); it++)
		if ( CarHit ( pCircle1, *it) )
			return true;
	return false;
}

bool ShotsColliding (Car pCar, list<Circle> &pCirclesList) {
	for (list<Circle>::iterator it = pCirclesList.begin(); it != pCirclesList.end(); it++)
		if ( CarHit ( *it, pCar) )
			return true;
	return false;
}

bool CarHit (Circle pShot, Car pCar) {
	GLfloat lDeltaX = pShot.getX() - pCar.getX();
	GLfloat lDeltaY = pShot.getY() - pCar.getY();
	GLfloat lXYRadiusSum = pShot.getRadius() + pCar.getRadius();
	bool lSameHeight = (pShot.getZ() <= (pCar.getZ() + pCar.getRadius()*0.7) )
											and (pShot.getZ() >= ( pCar.getZ() ) );
	return (lXYRadiusSum > sqrt(lDeltaX*lDeltaX + lDeltaY*lDeltaY)) and lSameHeight;
}

bool CircleCovered(Circle pInnerCircle, Circle pOuterCircle) {
	GLfloat lDeltaX = pInnerCircle.getX() - pOuterCircle.getX();
	GLfloat lDeltaY = pInnerCircle.getY() - pOuterCircle.getY();
	GLfloat lMaximumDistance = pOuterCircle.getRadius() - pInnerCircle.getRadius();
	return (lMaximumDistance > sqrt(lDeltaX*lDeltaX + lDeltaY*lDeltaY));
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
		return MoveObject(pCar, timeDiff, pSpeed);
	}
	else if (gKeyboardStatus[(int)('s')] and !gKeyboardStatus[(int)('w')]){
		return MoveObject(pCar, timeDiff, -pSpeed);
	}
	else
		return pCar;
}

Car RotateCar(Car pCar, GLdouble timeDiff , GLdouble pSpeed ) {
	if (gKeyboardStatus[(int)('w')] and !gKeyboardStatus[(int)('s')]) {
		if (gKeyboardStatus[(int)('a')] and !gKeyboardStatus[(int)('d')])
			pCar.incXYAngle(pSpeed * timeDiff);
		else if (gKeyboardStatus[(int)('d')] and !gKeyboardStatus[(int)('a')])
			pCar.incXYAngle(-pSpeed * timeDiff);
	}
	else if (gKeyboardStatus[(int)('s')] and !gKeyboardStatus[(int)('w')]) {
		if (gKeyboardStatus[(int)('a')] and !gKeyboardStatus[(int)('d')])
			pCar.incXYAngle(-pSpeed * timeDiff);
		else if (gKeyboardStatus[(int)('d')] and !gKeyboardStatus[(int)('a')])
			pCar.incXYAngle(pSpeed * timeDiff);
	}

	return pCar;
}
Car SteerCarWheels(Car pCar, GLdouble timeDiff , GLdouble pSpeed ) {
	if (gKeyboardStatus[(int)('a')] and !gKeyboardStatus[(int)('d')])
		pCar.setSteeringAngle(45);
	else if (gKeyboardStatus[(int)('d')] and !gKeyboardStatus[(int)('a')])
		pCar.setSteeringAngle(-45);
	else
		pCar.setSteeringAngle(0);

	return pCar;
}
Circle CarShot(Car pCar) {
	Circle lShot;
	lShot.setRadius(3);
	lShot.setRGB(1,1,0);
	lShot.setXYZPosition(pCar.getX(),pCar.getY(), pCar.getZLength());
	lShot.setXYAngle(pCar.getDegreeXYAngle());
	lShot = MoveObject(lShot, 1, pCar.body.getXLength()/2);
	lShot.incXYAngle(pCar.getDegreeGunXYAngle());
	lShot.incXZAngle(pCar.getDegreeGunXZAngle());
	lShot = MoveObject(lShot, 1, pCar.gun.getXLength());
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

void EnemyCarsShot(list<Car> &pCarsList, list<Circle> &pCirclesList, GLdouble timeDiff , GLdouble pFrequency) {
	static GLdouble lTime = 0;
	lTime += timeDiff;
	if ( (lTime * pFrequency) >= 1) {
		lTime = (lTime * pFrequency - 1)/pFrequency;
		for (list<Car>::iterator it = pCarsList.begin(); it != pCarsList.end(); it++)
			pCirclesList.push_back( CarShot(*it) );
	}
}

void CheckCompletedQuarter(Car pNewCar, Car pPreviousCar, Circle pOuterCircle, bool *pCompletedQuarter) {
	GLfloat lCenterX = pOuterCircle.getX();
	GLfloat lCenterY = pOuterCircle.getY();
	if (pPreviousCar.getX() > lCenterX)	{
	// right side, first and forth quarters
		if (pPreviousCar.getY() > lCenterY) {
		// First
			if ( (pNewCar.getX() < lCenterX) and (pNewCar.getY() > lCenterY) )
			// First quarter completed
				pCompletedQuarter[0] = true;
			else if ( (pNewCar.getX() > lCenterX) and (pNewCar.getY() < lCenterY) )
			// Forth returned
				pCompletedQuarter[3] = false;
		}
		else {
		// Forth
			if ( (pNewCar.getX() > lCenterX) and (pNewCar.getY() > lCenterY) )
			// Forth quarter completed
				pCompletedQuarter[3] = true and pCompletedQuarter[2];
			else if ( (pNewCar.getX() < lCenterX) and (pNewCar.getY() < lCenterY) )
			// Third returned
				pCompletedQuarter[2] = false;
		}
	}
	else {
	// left side, second and third quarters
		if (pPreviousCar.getY() > lCenterY) {
		// Second
			if ( (pNewCar.getX() < lCenterX) and (pNewCar.getY() < lCenterY) )
			// Second quarter completed
				pCompletedQuarter[1] = true and pCompletedQuarter[0];
			else if ( (pNewCar.getX() > lCenterX) and (pNewCar.getY() > lCenterY) )
			// First returned
				pCompletedQuarter[0] = false;
		}
		else {
		// Third
			if ( (pNewCar.getX() > lCenterX) and (pNewCar.getY() < lCenterY) )
			// Third quarter completed
				pCompletedQuarter[2] = true and pCompletedQuarter[1];
			else if ( (pNewCar.getX() < lCenterX) and (pNewCar.getY() > lCenterY) )
			// Second returned
				pCompletedQuarter[1] = false;
		}
	}
}

void TurnOnCarLight(Car pPlayerCar) {
  glEnable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHT1);
	GLfloat lightPosition[] = {0 , 0, 0, 1};
	GLfloat lightDirection[] = {1 , 0, 0};
	GLfloat lightAngle[] = {45};
	GLfloat lX = (GLfloat) pPlayerCar.getX();
	GLfloat lY = (GLfloat) pPlayerCar.getY();
	GLfloat lZ = (GLfloat) pPlayerCar.getZ();
	GLfloat lZLength = pPlayerCar.getZLength();

	glPushMatrix();
		glTranslatef(lX,lY,lZ);
		glTranslatef(0,0,lZLength);
	  glRotatef(pPlayerCar.getDegreeXYAngle(),0,0,1);
	  glTranslatef(pPlayerCar.body.getXLength()/2, 0, 0);
		glPushMatrix();
	  	glTranslatef(0, pPlayerCar.body.getYLength()/2, 0);
		  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);
		  glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, lightAngle);
  		glEnable(GL_LIGHT0);
		glPopMatrix();
		glPushMatrix();
	  	glTranslatef(0, -pPlayerCar.body.getYLength()/2, 0);
		  glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
		  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDirection);
		  glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, lightAngle);
  		glEnable(GL_LIGHT1);
		glPopMatrix();
	glPopMatrix();
}

void TurnOnTrackLight(Circle pOuterCircle) {
  glEnable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHT1);


	GLfloat lightPosition[] = {0, 0, 0, 1};
	GLfloat lightDirection[] = {0 , 0, -1};
	GLfloat lightAngle[] = {180};

	glPushMatrix();
		glTranslatef(pOuterCircle.getX(),pOuterCircle.getY(),100);
	  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);
	  glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, lightAngle);
	  glEnable(GL_LIGHT0);
	glPopMatrix();
}
