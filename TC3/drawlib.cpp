#include "drawlib.h"
#include <cmath>

void drawColor(Object pObject) {
	glColor3f(pObject.getR(), pObject.getG(), pObject.getB());
}

void draw(Rectangle pRectangle) {
	if (!pRectangle.getVisible())
		return;
	GLfloat lHalfWidth = (GLfloat) pRectangle.getWidth()/(2);
	GLfloat lHalfHeight = (GLfloat) pRectangle.getHeight()/(2);
	GLfloat lX = (GLfloat) pRectangle.getX();
	GLfloat lY = (GLfloat) pRectangle.getY();
	glPushMatrix();
	glTranslatef(lX,lY,0);
	drawColor(pRectangle);
	glBegin(GL_POLYGON);
		glVertex3f( -lHalfWidth, -lHalfHeight,0.0);    
		glVertex3f(  lHalfWidth, -lHalfHeight,0.0);    
		glVertex3f(  lHalfWidth,  lHalfHeight,0.0);    
		glVertex3f( -lHalfWidth,  lHalfHeight,0.0);
	glEnd(); 
	glPopMatrix();
}

void draw(Circle pCircle) {
	if (!pCircle.getVisible())
		return;
	GLfloat lX = (GLfloat) pCircle.getX();
	GLfloat lY = (GLfloat) pCircle.getY();
	GLfloat lRadius = (GLfloat) pCircle.getRadius();
	int i;
	int triangleAmount = 100; //# of triangles used to draw circle
	
	GLfloat twicePi = 2.0f * M_PI;
	
	glPushMatrix();
	glTranslatef(lX,lY,0);
	drawColor(pCircle);	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0, 0); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		    (lRadius * cos(i *  twicePi / triangleAmount)), 
			  (lRadius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
	glPopMatrix();
}