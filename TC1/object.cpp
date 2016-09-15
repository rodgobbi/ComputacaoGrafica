#include "classes.h"

void Object::setRGB(GLfloat pR, GLfloat pG, GLfloat pB) {
	R = pR;
	G = pG;
	B = pB;
}
void Object::setPosition(GLint pX, GLint pY){
	X = pX;
	Y = pY;
}
GLint Object::getX() {
	return X;
}
GLint Object::getY() {
	return Y;
}
GLfloat Object::getR() {
	return R;
}
GLfloat Object::getG() {
	return G;
}
GLfloat Object::getB() {
	return B;
}