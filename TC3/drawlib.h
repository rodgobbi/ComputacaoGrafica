#ifndef DRAWLIB
#define DRAWLIB
#include <GL/glut.h>
#include "classlib.h"

void drawColor(Object pObject);

void draw(Rectangle pRectangle);

void draw(Circle pCircle);

void draw(Car pCar);

void drawWheels(Car pCar);

void drawGun(Car pCar);

#endif