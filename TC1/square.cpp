#include "classlib.h"

void Square::setSize(GLsizei pSize) {
	size = pSize;
}

GLsizei Square::getSize() {
	return size;
}

bool Square::pointIsInside(GLint pX, GLint pY) {
	GLsizei lHalfSize = size/2;
	if ( (pX >= (X - lHalfSize) ) and (pX <= (X + lHalfSize) ) and (pY >= (Y - lHalfSize) ) and (pY <= (Y + lHalfSize) ) )
		return true;
	else
		return false;
}