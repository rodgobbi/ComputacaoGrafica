#include "drawlib.h"
#include <cmath>

void drawColor(Object pObject) {
	glColor3f(pObject.getR(), pObject.getG(), pObject.getB());
}

void draw(Rectangle pRectangle, GLsizei pWindowW, GLsizei pWindowH) {
	if (!pRectangle.getVisible())
		return;
	GLfloat lHalfWidth = (GLfloat) pRectangle.getWidth()/(pWindowW*2);
	GLfloat lHalfHeight = (GLfloat) pRectangle.getHeight()/(pWindowH*2);
	GLfloat lX = (GLfloat) pRectangle.getX()/pWindowW;
	GLfloat lY = (GLfloat) pRectangle.getY()/pWindowH;
	drawColor(pRectangle);
	glBegin(GL_POLYGON);
		glVertex3f(lX - lHalfWidth,lY - lHalfHeight,0.0);    
		glVertex3f(lX + lHalfWidth,lY - lHalfHeight,0.0);    
		glVertex3f(lX + lHalfWidth,lY + lHalfHeight,0.0);    
		glVertex3f(lX - lHalfWidth,lY + lHalfHeight,0.0);
	glEnd(); 
}

void draw(Circle pCircle, GLsizei pWindowW, GLsizei pWindowH) {
	if (!pCircle.getVisible())
		return;
	GLfloat lX = (GLfloat) pCircle.getX()/pWindowW;
	GLfloat lY = (GLfloat) pCircle.getY()/pWindowH;
	GLfloat lXRadius = (GLfloat) pCircle.getRadius()/pWindowW;
	GLfloat lYRadius = (GLfloat) pCircle.getRadius()/pWindowH;
	int i;
	int triangleAmount = 100; //# of triangles used to draw circle
	
	GLfloat twicePi = 2.0f * M_PI;
	
	drawColor(pCircle);
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(lX, lY); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		    lX + (lXRadius * cos(i *  twicePi / triangleAmount)), 
			  lY + (lYRadius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}