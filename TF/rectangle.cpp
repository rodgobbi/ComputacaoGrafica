#include "classlib.h"

Rectangle::Rectangle() {
	visible = true;
	X = 0;
	Y = 0;
	Z = 0;
	XYAngle = 0;
	XZAngle = 0;
}

void Rectangle::setXLength(GLfloat pW) {
	XLength = pW;
}

GLfloat Rectangle::getXLength() {
	return XLength;
}

void Rectangle::setYLength(GLfloat pH) {
	YLength = pH;
}

GLfloat Rectangle::getYLength() {
	return YLength;
}

Rectangle3d::Rectangle3d() {
	visible = true;
	X = 0;
	Y = 0;
	Z = 0;
	XYAngle = 0;
	XZAngle = 0;
}

void Rectangle3d::setZLength(GLfloat pW) {
	ZLength = pW;
}

GLfloat Rectangle3d::getZLength() {
	return ZLength;
}