#ifndef CLASSLIB
#define CLASSLIB
#include <GL/glut.h>
#include <string.h>
#include <iostream>
using namespace std;

class Object
{
public:
	void setRGB(GLfloat pR, GLfloat pG, GLfloat pB);
	void setColor(string pColor);
	void setPosition(GLfloat pX, GLfloat pY);
	void incX(GLfloat pX);
	void incY(GLfloat pY);
	GLfloat getX();
	GLfloat getY();
	GLfloat getR();
	GLfloat getG();
	GLfloat getB();
	void setVisible(bool pVisible);
	bool getVisible();
protected:
	GLfloat R, G, B, X, Y;
	bool visible;
};

class Circle : public Object
{
public:
	Circle();
	void setRadius(GLfloat pRadius);
	GLfloat getRadius();
	// bool pointIsInside(GLint pX, GLint pY);
protected:
	GLfloat radius;
};

class Rectangle : public Object
{
public:
	Rectangle();	
	void setWidth(GLsizei pW);
	void setHeight(GLsizei pH);
	GLsizei getWidth();
	GLsizei getHeight();
	// bool pointIsInside(GLint pX, GLint pY);
protected:
	GLsizei width, height;
};

class Car : public Circle
{
public:
	Car();
	void setDirection(GLfloat pAngleDirection);
	GLfloat getDirection();
	void incAngleDirection(GLfloat pAngle);
protected:
	GLfloat direction;	
};

#endif