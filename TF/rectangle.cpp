#include "classlib.h"

Rectangle::Rectangle() {
	visible = true;
	X = 0;
	Y = 0;
}

void Rectangle::setWidth(GLsizei pW) {
	width = pW;
}

GLsizei Rectangle::getWidth() {
	return width;
}

void Rectangle::setHeight(GLsizei pH) {
	height = pH;
}

GLsizei Rectangle::getHeight() {
	return height;
}
