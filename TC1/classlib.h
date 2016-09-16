#ifndef CLASSLIB
#define CLASSLIB
#include <GL/glut.h>

class Object
{
public:
	// Object();
	// ~Object();
	void setRGB(GLfloat pR, GLfloat pG, GLfloat pB);
	void setPosition(GLint pX, GLint pY);
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

class Square : public Object
{
public:
	// Square();
	// ~Square();
	void setSize(GLsizei pSize);
	GLsizei getSize();
	bool pointIsInside(GLint pX, GLint pY);
protected:
	GLsizei size;
};

#endif