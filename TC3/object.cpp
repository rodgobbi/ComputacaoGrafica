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
	else if (pColor == "grayblue")
		this->setRGB(0.6,0.6,0.8);
	else if (pColor == "moss")
		this->setRGB(0,0.6,0);
	else if (pColor == "darkmoss")
		this->setRGB(0,0.2,0);
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
void Object::setDirection(GLfloat pAngleDirection) {
	direction = fmod(pAngleDirection, 360.0);
}
GLfloat Object::getRadianDirection() {
	return direction * M_PI / 180;
}
GLfloat Object::getDegreeDirection() {
	return direction;
}
void Object::incDirectionAngle(GLfloat pAngle) {
	direction = fmod((direction + pAngle), 360.0);
}