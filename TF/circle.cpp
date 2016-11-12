#include "classlib.h"

Circle::Circle() {
	visible = true;
	radius = 0;
	X = 0;
	Y = 0;
	Z = 0;
	XYAngle = 0;
	XZAngle = 0;
}

void Circle::setRadius(GLfloat pRadius) {
	radius = pRadius;
}

GLfloat Circle::getRadius() {
	return radius;
}
