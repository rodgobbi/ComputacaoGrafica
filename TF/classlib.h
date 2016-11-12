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
	void setXYPosition(GLfloat pX, GLfloat pY);
	void incX(GLfloat pX);
	void incY(GLfloat pY);
	GLfloat getX();
	GLfloat getY();
	GLfloat getR();
	GLfloat getG();
	GLfloat getB();
	void setVisible(bool pVisible);
	bool getVisible();
	void setXYAngle(GLfloat pAngle);
	GLfloat getRadianXYAngle();
  GLfloat getDegreeXYAngle();
	void incXYAngle(GLfloat pAngle);
protected:
	GLfloat R, G, B, X, Y, XYAngle;
	bool visible;
};

class Object3d : public Object
{
public:
	void setXYZPosition(GLfloat pX, GLfloat pY, GLfloat pZ);
	void incZ(GLfloat pZ);
	GLfloat getZ();
	void setXZAngle(GLfloat pAngle);
	GLfloat getRadianXZAngle();
  GLfloat getDegreeXZAngle();
	void incXZAngle(GLfloat pAngle);
protected:
	GLfloat Z, XZAngle;
};

class Circle : public Object3d
{
public:
	Circle();
	void setRadius(GLfloat pRadius);
	GLfloat getRadius();
	// bool pointIsInside(GLint pX, GLint pY);
protected:
	GLfloat radius;
};

class Rectangle : public Object3d
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
  Rectangle body, gun, hub, wheel, wheelStripe;
	Car();
	void setGunDirection(GLfloat pAngleDirection);
  GLfloat getDegreeGunDirection();
	void incGunDirectionAngle(GLfloat pAngle);
  void setRadius(GLfloat pRadius);  
	void setSteeringAngle(GLfloat pAngle);
	GLfloat getDegreeSteeringAngle();
	void setWheelStripePosition(GLfloat pPercentage);
	GLfloat getWheelStripePosition();
	void incWheelStripePosition(GLfloat pPercentage);
protected:
	GLfloat gunDirection, steeringAngle, wheelStripePosition;
};

class Controller
{
public:
	void setCarControlled(Car *pCarAddress);
	Car* getCar();
	GLdouble movTime;
	bool turnLeft;
	bool foward;
	bool turning;
private:
	Car* carControlled;
};

#endif