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
	void setRadius(GLsizei pRadius);
	GLsizei getRadius();
	// bool pointIsInside(GLint pX, GLint pY);
protected:
	GLsizei radius;
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

#endif