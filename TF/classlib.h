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
	void setXLength(GLfloat pW);
	void setYLength(GLfloat pH);
	GLfloat getXLength();
	GLfloat getYLength();
	// bool pointIsInside(GLint pX, GLint pY);
protected:
	GLfloat XLength, YLength;
};

class Rectangle3d : public Rectangle {
public:
	Rectangle3d();	
	void setZLength(GLfloat pW);
	GLfloat getZLength();
protected:
	GLfloat ZLength;
};

class Cylinder : public Object3d 
{
public:
	Cylinder();
	void setXLength(GLfloat pW);
	GLfloat getXLength();
	void setRadius(GLfloat pRadius);
	GLfloat getRadius();
protected:
	GLfloat XLength, radius;
};

class Car : public Circle
{
public:
  Rectangle body, gun, hub, wheel, wheelStripe;
	Car();
	void setGunXYAngle(GLfloat pAngle);
  GLfloat getDegreeGunXYAngle();
	void incGunXYAngle(GLfloat pAngle);
	void setGunXZAngle(GLfloat pAngle);
  GLfloat getDegreeGunXZAngle();
	void incGunXZAngle(GLfloat pAngle);
  void setRadius(GLfloat pRadius);  
	void setSteeringAngle(GLfloat pAngle);
	GLfloat getDegreeSteeringAngle();
protected:
	GLfloat gunXYAngle, gunXZAngle, steeringAngle;
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