#include "classlib.h"

void Object::setRGB(GLfloat pR, GLfloat pG, GLfloat pB) {
	R = pR;
	G = pG;
	B = pB;
}

void Object::setColor(string pColor) {
	if (pColor == "blue")
		this->setRGB(0,0,1);
	else if (pColor == "white")
		this->setRGB(1,1,1);
	else if (pColor == "black")
		this->setRGB(0,0,0);
	else if (pColor == "red")
		this->setRGB(1,0,0);
	else if (pColor == "green")
		this->setRGB(0,1,0);
}

void Object::setPosition(GLfloat pX, GLfloat pY){
	X = pX;
	Y = pY;
}
void Object::incX(GLfloat pX) {
	X = X + pX;
}
void Object::incY(GLfloat pY) {
	Y = Y + pY;
}
GLfloat Object::getX() {
	return X;
}
GLfloat Object::getY() {
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
void Object::setVisible(bool pVisible) {
	visible = pVisible;
}
bool Object::getVisible() {
	return visible;
}