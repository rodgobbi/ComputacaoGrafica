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

void Object::setXYPosition(GLfloat pX, GLfloat pY){
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
void Object::setXYAngle(GLfloat pAngle) {
	XYAngle = fmod(pAngle, 360.0);
}
GLfloat Object::getRadianXYAngle() {
	return XYAngle * M_PI / 180;
}
GLfloat Object::getDegreeXYAngle() {
	return XYAngle;
}
void Object::incXYAngle(GLfloat pAngle) {
	XYAngle = fmod((XYAngle + pAngle), 360.0);
}


void Object3d::setXYZPosition(GLfloat pX, GLfloat pY, GLfloat pZ){
	X = pX;
	Y = pY;
	Z = pZ;
}
void Object3d::incZ(GLfloat pZ) {
	Z = Z + pZ;
}
GLfloat Object3d::getZ() {
	return Z;
}
void Object3d::setXZAngle(GLfloat pAngle) {
	XZAngle = fmod(pAngle, 360.0);
}
GLfloat Object3d::getRadianXZAngle() {
	return XZAngle * M_PI / 180;
}
GLfloat Object3d::getDegreeXZAngle() {
	return XZAngle;
}
void Object3d::incXZAngle(GLfloat pAngle) {
	XZAngle = fmod((XZAngle + pAngle), 360.0);
}