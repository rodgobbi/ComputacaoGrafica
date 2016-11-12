#include "classlib.h"

Cylinder::Cylinder() {
	visible = true;
	X = 0;
	Y = 0;
	Z = 0;
	XYAngle = 0;
	XZAngle = 0;
}

void Cylinder::setXLength(GLfloat pW) {
	XLength = pW;
}

GLfloat Cylinder::getXLength() {
	return XLength;
}

void Cylinder::setRadius(GLfloat pRadius) {
	radius = pRadius;
}

GLfloat Cylinder::getRadius() {
	return radius;
}
