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

void draw(Car pCar) {
	if (!pCar.getVisible())
		return;	
	GLfloat lX = (GLfloat) pCar.getX();
	GLfloat lY = (GLfloat) pCar.getY();

	glPushMatrix();
		glTranslatef(lX,lY,0);
	  glRotatef(pCar.getDegreeDirection(),0,0,1);
	  draw(pCar.body);
	  drawColor(pCar.gun);
	  drawEllipse(pCar.body.getWidth()/4, pCar.body.getHeight()/4);
	  drawWheels(pCar);
	  drawGun(pCar);
	glPopMatrix();
}

void drawWheels(Car pCar) {
	GLfloat lHubX = (pCar.body.getWidth()/2)*0.7;
	GLfloat lHubY = (pCar.body.getHeight()/2) + (pCar.hub.getHeight()/2);
	GLfloat lWheelX = lHubX;
	GLfloat lWheelY = lHubY + (pCar.hub.getHeight()/2) + (pCar.wheel.getHeight()/2);
	GLfloat lWheelStripeXPosition = (pCar.getWheelStripePosition() - 0.5)*pCar.wheel.getWidth();

	// front
	pCar.hub.setPosition(lHubX,lHubY);
	draw(pCar.hub);

	glPushMatrix();
		glTranslatef(lWheelX,lWheelY,0);
		glRotatef(pCar.getDegreeSteeringAngle(),0,0,1);
		pCar.wheel.setPosition(0,0);
		draw(pCar.wheel);
		pCar.wheelStripe.setPosition(lWheelStripeXPosition,0);
		draw(pCar.wheelStripe);
	glPopMatrix();

	pCar.hub.setPosition(lHubX,-lHubY);
	draw(pCar.hub);	

	glPushMatrix();
		glTranslatef(lWheelX,-lWheelY,0);
		glRotatef(pCar.getDegreeSteeringAngle(),0,0,1);
		pCar.wheel.setPosition(0,0);
		draw(pCar.wheel);
		pCar.wheelStripe.setPosition(lWheelStripeXPosition,0);
		draw(pCar.wheelStripe);
	glPopMatrix();

	// rear
	pCar.hub.setPosition(-lHubX,lHubY);
	pCar.wheel.setPosition(-lWheelX,lWheelY);
	pCar.wheelStripe.setPosition(-lWheelX + lWheelStripeXPosition, lWheelY);
	draw(pCar.hub);
	draw(pCar.wheel);
	draw(pCar.wheelStripe);
	pCar.hub.setPosition(-lHubX,-lHubY);
	pCar.wheel.setPosition(-lWheelX,-lWheelY);
	pCar.wheelStripe.setPosition(-lWheelX + lWheelStripeXPosition,-lWheelY);
	draw(pCar.hub);
	draw(pCar.wheel);
	draw(pCar.wheelStripe);
}

void drawGun(Car pCar) {
	glPushMatrix();
		glTranslatef(pCar.body.getWidth()/2,0,0);
	  glRotatef(pCar.getDegreeGunDirection(),0,0,1);
		glTranslatef(pCar.gun.getWidth()/2,0,0);
		draw(pCar.gun);
	glPopMatrix();
}

void drawEllipse(GLfloat radiusX, GLfloat radiusY) {
	int i;

	glBegin(GL_TRIANGLE_FAN);		
		glVertex2f(0, 0); 	
		for(i=0;i<360;i++) {
		  GLfloat rad = i*M_PI/180;
		  glVertex2f(cos(rad)*radiusX,
		              sin(rad)*radiusY);
		}
	glEnd();
}