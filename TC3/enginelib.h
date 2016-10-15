#ifndef ENGINELIB
#define ENGINELIB
#include <GL/glut.h>
#include "classlib.h"
#include <cmath>
#include <list>
using namespace std;

extern Circle gOuterCircle, gInnerCircle;
extern Car gPlayerCar;
extern Rectangle gStripeRect;
extern bool gKeyboardStatus[256];
extern GLfloat gMovementSpeed, gRotationSpeed;
extern list<Circle> gEnemiesList;
extern list<Circle> gShotsList;

bool CirclesColliding (Circle pCircle1, Circle pCircle2);
bool CirclesColliding (Circle pCircle1, list<Circle> pCirclesList);
bool CircleCovered(Circle pInnerCircle, Circle pOuterCircle);
template<class tObject>
tObject MoveObject(tObject pObject, GLdouble timeDiff , GLdouble pSpeed);
void MoveShots(list<Circle> gShotsList, GLdouble timeDiff , GLdouble pSpeed);
Car MoveCar(Car pCar, GLdouble timeDiff , GLdouble pSpeed );
Car RotateCar(Car pCar, GLdouble timeDiff , GLdouble pSpeed );
Car SteerCarWheels(Car pCar, GLdouble timeDiff , GLdouble pSpeed );

#endif