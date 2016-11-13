#ifndef ENGINELIB
#define ENGINELIB
#include <GL/glut.h>
#include "classlib.h"
#include <cmath>
#include <list>
using namespace std;

extern bool gKeyboardStatus[256];

bool CirclesColliding (Circle pCircle1, Circle pCircle2);
bool CirclesColliding (Circle pCircle1, list<Circle> &pCirclesList);
bool CirclesColliding (Circle pCircle1, list<Car> &pCarsList);
bool CircleCovered(Circle pInnerCircle, Circle pOuterCircle);
void MoveShots(list<Circle> &pShotsList, GLdouble timeDiff , GLdouble pSpeed, Circle pOuterCircle);
Car MoveCar(Car pCar, GLdouble timeDiff , GLdouble pSpeed );
Car RotateCar(Car pCar, GLdouble timeDiff , GLdouble pSpeed );
Car SteerCarWheels(Car pCar, GLdouble timeDiff , GLdouble pSpeed );
Circle CarShot(Car pCar);
bool PointOutOfWindow(Object pObject, Circle pOuterCircle);
void EnemyCarsShot(list<Car> &pCarsList, list<Circle> &pCirclesList, GLdouble timeDiff , GLdouble pFrequency);
void CheckCompletedQuarter(Car pNewCar, Car pPreviousCar, Circle pOuterCircle, bool *pCompletedQuarter);
void TurnOnCarLight(Car pPlayerCar);
void TurnOnTrackLight(Circle pOuterCircle);

template<class tObject>
tObject MoveObject(tObject pObject, GLdouble timeDiff , GLdouble pSpeed) {
	GLfloat lDirection = pObject.getRadianXYAngle();
	pObject.incX(pSpeed * timeDiff * cos(lDirection) );
	pObject.incY(pSpeed * timeDiff * sin(lDirection) );
	return pObject;
}

#endif