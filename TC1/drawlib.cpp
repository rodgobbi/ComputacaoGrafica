#include "drawlib.h"

void drawColor(Object pObject) {
	glColor3f(pObject.getR(), pObject.getG(), pObject.getB());
}

void draw(Square pSquare, GLsizei pW, GLsizei pH) {
	if (!pSquare.getVisible())
		return;
	GLfloat lHalfWidth = (GLfloat) pSquare.getSize()/(pW*2);
	GLfloat lHalfHeight = (GLfloat) pSquare.getSize()/(pH*2);
	GLfloat lX = (GLfloat) pSquare.getX()/pW;
	GLfloat lY = (GLfloat) pSquare.getY()/pH;
	drawColor(pSquare);
	glBegin(GL_POLYGON);
		glVertex3f(lX - lHalfWidth,lY - lHalfHeight,0.0);    
		glVertex3f(lX + lHalfWidth,lY - lHalfHeight,0.0);    
		glVertex3f(lX + lHalfWidth,lY + lHalfHeight,0.0);    
		glVertex3f(lX - lHalfWidth,lY + lHalfHeight,0.0);
	glEnd(); 
}