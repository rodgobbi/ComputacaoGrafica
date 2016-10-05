#include "classlib.h"

Circle::Circle() {
	visible = true;
}

void Circle::setRadius(GLfloat pRadius) {
	radius = pRadius;
}

GLfloat Circle::getRadius() {
	return radius;
}