#ifndef CLASSES
#define CLASSES
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
protected:
	GLfloat R, G, B;
	GLint X, Y;
};

class Square : public Object
{
public:
	// Square();
	// ~Square();
	void setSize(GLsizei pSize);
	GLsizei getSize();
protected:
	GLsizei size;
};

#endif