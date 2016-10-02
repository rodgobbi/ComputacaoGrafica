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
	void setPosition(GLint pX, GLint pY);
	void incX(GLint pX);
	void incY(GLint pY);
	GLint getX();
	GLint getY();
	GLfloat getR();
	GLfloat getG();
	GLfloat getB();
	void setVisible(bool pVisible);
	bool getVisible();
protected:
	GLfloat R, G, B;
	GLint X, Y;
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