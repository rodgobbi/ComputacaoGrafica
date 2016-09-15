#ifndef CLASSES
#define CLASSES
#include <GL/glut.h>
#include "drawlib.h"

class Object
{
public:
	// Object();
	// ~Object();
	void setRGB(GLfloat pR, GLfloat pG, GLfloat pB);
	void setPosition(GLint pX, GLint pY);
	GLint getX();
	GLint getY();
protected:
	GLfloat R, G, B;
	GLint X, Y;
};

class Square : public Object
{
public:
	// Square();
	// ~Square();
	void setSize(GLint pSize);
	friend void draw(Square pSquare);
protected:
	GLint size;
};

#endif