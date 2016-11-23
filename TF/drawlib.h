#ifndef DRAWLIB
#define DRAWLIB
#include <GL/glut.h>
#include "classlib.h"
#include <stdio.h>
#include <list>
using namespace std;

void drawColor(Object pObject);
void draw(Rectangle pRectangle);
void drawRectangle3d(Rectangle3d pRectangle);
void draw(Circle pCircle);
void drawFlatSphere(Circle pCircle);
void drawSphere(Circle pCircle);
void draw(Car pCar);
void drawWheels(Car pCar);
void drawGun(Car pCar);
void drawEllipse(GLfloat radiusX, GLfloat radiusY);
void drawEllipse3d(GLfloat radiusX, GLfloat radiusY);
void drawCylinder(Cylinder pCylinder);
void drawTime(Circle pOuterCircle, GLdouble pMilisecTime);
void drawGameOver(Circle pOuterCircle, bool pWin);
void setThirdPersonCamera(Car pPlayerCar, GLfloat pXYDegreeAngle, GLfloat pXZDegreeAngle);
void setCockpitCamera(Car pPlayerCar);
void setGunCamera(Car pPlayerCar, bool pInverted);
void drawInnerWall(Circle pInnerCircle, Car pPlayerCar);
void drawOuterWall(Circle pOuterCircle, Car pPlayerCar);
void TurnOnCarLight(Car pPlayerCar);
void TurnOnTrackLight(Circle pOuterCircle);
void drawMap(Circle pOuterCircle, Circle pInnerCircle, Circle pPlayerCar, list<Car> &pCarsList);
void drawCircleLine( Circle pCircle);
#endif
