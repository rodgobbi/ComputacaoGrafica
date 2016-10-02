#include "classlib.h"

Circle::Circle() {
	visible = true;
}

void Circle::setRadius(GLsizei pRadius) {
	radius = pRadius;
}

GLsizei Circle::getRadius() {
	return radius;
}