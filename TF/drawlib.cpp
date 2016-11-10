#include "drawlib.h"
#include <cmath>

void drawColor(Object pObject) {
	glColor3f(pObject.getR(), pObject.getG(), pObject.getB());
	GLfloat material[] = {pObject.getR(), pObject.getG(), pObject.getB(),1};
  GLfloat no_mat[] = {0,0,0,1};
  GLfloat mat_specular[] = {pObject.getR(), pObject.getG(), pObject.getB(),1};
  GLfloat mat_shininess[] = {0.3};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
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
		// glScalef(2*lHalfWidth, 2*lHalfHeight, 1);
		glScalef( lHalfWidth, lHalfHeight, lHalfHeight);
    // glutSolidCube(1.0);
		glBegin(GL_POLYGON);
			glNormal3f(0,0,1);	
			glVertex3f( -1, -1,0.0);
			glNormal3f(0,0,1);	    
			glVertex3f(  1, -1,0.0);
			glNormal3f(0,0,1);	    
			glVertex3f(  1,  1,0.0); 
			glNormal3f(0,0,1); 	  
			glVertex3f( -1,  1,0.0);
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
	// glScalef( lRadius, lRadius, 1);
	// glutSolidSphere(1,100,16);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0,0,1);
		glVertex3f(0, 0, 0); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glNormal3f(0,0,1);
			glVertex3f(
		    (lRadius * cos(i *  twicePi / triangleAmount)), 
			  (lRadius * sin(i * twicePi / triangleAmount)),
			  0
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
	GLfloat lZ = (GLfloat) pCar.getRadius()/2;

	glPushMatrix();
		glTranslatef(lX,lY,lZ);
	  glRotatef(pCar.getDegreeDirection(),0,0,1);
	  drawColor(pCar.gun);
	  drawEllipse(pCar.body.getWidth()/4, pCar.body.getHeight()/4);
	  draw(pCar.body);
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
		glVertex3f(0, 0, 0); 	
		for(i=0;i<360;i++) {
		  GLfloat rad = i*M_PI/180;
		  glVertex3f(cos(rad)*radiusX,
		              sin(rad)*radiusY,
		              0 );
		}
	glEnd();
}

void drawTime(Circle pOuterCircle, GLdouble pMilisecTime) {
  glMatrixMode (GL_MODELVIEW);
  glPushMatrix();
	  glLoadIdentity();
		glMatrixMode (GL_PROJECTION);
	  glPushMatrix();
	    glLoadIdentity ();
	    glOrtho (0, 1, 0, 1, -1, 1);  
			glPushAttrib(GL_ENABLE_BIT);
			  glDisable(GL_LIGHTING);
			  glDisable(GL_TEXTURE_2D);
				int sec = ((int) pMilisecTime/1000)%60;
				int min = (((int) pMilisecTime/1000)/60)%60;
				char timeString[6];
				if (min < 10)
					if (sec < 10)
						sprintf(timeString, "0%d:0%d", min, sec);
					else
						sprintf(timeString, "0%d:%d", min, sec);
				else
					if (sec < 10)
						sprintf(timeString, "%d:0%d", min, sec);
					else
						sprintf(timeString, "%d:%d", min, sec);
				glColor3f(0,0,0);
				glRasterPos2f(0.9, 0.95);
				for (int i = 0; i < 5; i++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, timeString[i]);
				}
			glPopAttrib(); 
	  glPopMatrix();
	  glMatrixMode (GL_MODELVIEW);
  glPopMatrix();
}

void drawGameOver(Circle pOuterCircle, bool pWin) {
  glMatrixMode (GL_MODELVIEW);
	glPushMatrix();
	  glLoadIdentity();
		glMatrixMode (GL_PROJECTION);
	  glPushMatrix();
	    glLoadIdentity ();
	    glOrtho (0, 1, 0, 1, -1, 1);  
		  glPushAttrib(GL_ENABLE_BIT);
			  glDisable(GL_LIGHTING);
			  glDisable(GL_TEXTURE_2D);
	      glColor3f(0,1,0);
				char lString[20];
				if (pWin) {
					sprintf(lString, "You win! :)");
					glRasterPos2f(0.45, 0.5);
					}
				else {
					sprintf(lString, "You lose! :(");
					glRasterPos2f(0.40, 0.5);
					}
				for (int i = 0; lString[i]; ++i) {		
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, lString[i]);
				}
		  glPopAttrib();  
	  glPopMatrix();
	  glMatrixMode (GL_MODELVIEW);
  glPopMatrix();
}