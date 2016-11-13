#ifndef DRAWLIB
#define DRAWLIB
#include <GL/glut.h>
#include "classlib.h"
#include <stdio.h>

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

#endif