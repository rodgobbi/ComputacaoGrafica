#ifndef CLASSLIB
#define CLASSLIB
#include <GL/glut.h>
#include <string.h>
#include <iostream>
using namespace std;
#include <cmath>

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
	void setDirection(GLfloat pAngleDirection);
	GLfloat getRadianDirection();
  GLfloat getDegreeDirection();
	void incDirectionAngle(GLfloat pAngle);
protected:
	GLfloat R, G, B, X, Y, direction;
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
  Rectangle body, gun, hub, wheel;
	Car();
	void setGunDirection(GLfloat pAngleDirection);
  GLfloat getDegreeGunDirection();
	void incGunDirectionAngle(GLfloat pAngle);
  void setRadius(GLfloat pRadius);  
	void setSteeringAngle(GLfloat pAngle);
	GLfloat getDegreeSteeringAngle();
protected:
	GLfloat gunDirection, steeringAngle;
};

#endif