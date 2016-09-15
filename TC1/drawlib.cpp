#include "drawlib.h"

void drawColor(Object pObject) {
	glColor3f(pObject.R, pObject.G, pObject.B);
}

void draw(Square pSquare) {
	GLfloat lHalfSize = pSquare.size/2;
	GLfloat lX = pSquare.X;
	GLfloat lY = pSquare.Y;
	drawColor(pSquare);
	glBegin(GL_POLYGON);
		glVertex3f(lX - lHalfSize,lY - lHalfSize,0.0);    
		glVertex3f(lX + lHalfSize,lY - lHalfSize,0.0);    
		glVertex3f(lX + lHalfSize,lY + lHalfSize,0.0);    
		glVertex3f(lX - lHalfSize,lY + lHalfSize,0.0);
	glEnd(); 
}