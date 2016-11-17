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
	GLfloat lHalfWidth = (GLfloat) pRectangle.getXLength()/(2);
	GLfloat lHalfHeight = (GLfloat) pRectangle.getYLength()/(2);
	GLfloat lX = (GLfloat) pRectangle.getX();
	GLfloat lY = (GLfloat) pRectangle.getY();
	glPushMatrix();
		glTranslatef(lX,lY,0);
		drawColor(pRectangle);
		// glScalef(2*lHalfWidth, 2*lHalfHeight, 1);
		glScalef( lHalfWidth, lHalfHeight, 1);
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

void drawRectangle3d(Rectangle3d pRectangle) {
	if (!pRectangle.getVisible())
		return;
	GLfloat lXLength = (GLfloat) pRectangle.getXLength();
	GLfloat lYLength = (GLfloat) pRectangle.getYLength();
	GLfloat lZLength = (GLfloat) pRectangle.getZLength();
	GLfloat lX = (GLfloat) pRectangle.getX();
	GLfloat lY = (GLfloat) pRectangle.getY();
	GLfloat lZ = (GLfloat) pRectangle.getZ();
	glPushMatrix();
		glTranslatef(lX,lY,lZ);
		drawColor(pRectangle);
		glScalef( lXLength, lYLength, lZLength);
    glutSolidCube(1.0);
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
		glScalef( lRadius, lRadius, 1);
		glBegin(GL_TRIANGLE_FAN);
			glNormal3f(0,0,1);
			glVertex3f(0, 0, 0); // center of circle
			for(i = 0; i <= triangleAmount;i++) {
				glNormal3f(0,0,1);
				glVertex3f(
			    (1 * cos(i *  twicePi / triangleAmount)),
				  (1 * sin(i * twicePi / triangleAmount)),
				  0
				);
			}
		glEnd();
	glPopMatrix();
}

void drawFlatSphere(Circle pCircle) {
	if (!pCircle.getVisible())
		return;
	GLfloat lX = (GLfloat) pCircle.getX();
	GLfloat lY = (GLfloat) pCircle.getY();
	GLfloat lRadius = (GLfloat) pCircle.getRadius();

	glPushMatrix();
		glTranslatef(lX,lY,0);
		drawColor(pCircle);
		glScalef( lRadius, lRadius, 1);
		glutSolidSphere(1,100,100);
	glPopMatrix();
}

void drawSphere(Circle pCircle) {
	if (!pCircle.getVisible())
		return;
	GLfloat lX = (GLfloat) pCircle.getX();
	GLfloat lY = (GLfloat) pCircle.getY();
	GLfloat lZ = (GLfloat) pCircle.getZ();
	GLfloat lRadius = (GLfloat) pCircle.getRadius();

	glPushMatrix();
		glTranslatef(lX,lY,lZ);
		drawColor(pCircle);
		glScalef( lRadius, lRadius, lRadius);
		glutSolidSphere(1,16,16);
	glPopMatrix();
}

void draw(Car pCar) {
	if (!pCar.getVisible())
		return;
	GLfloat lX = (GLfloat) pCar.getX();
	GLfloat lY = (GLfloat) pCar.getY();
	GLfloat lZ = (GLfloat) pCar.getZ();
	GLfloat lZLength = pCar.getZLength();

	glPushMatrix();
		glTranslatef(lX,lY,lZ);
		glTranslatef(0,0,lZLength);
	  glRotatef(pCar.getDegreeXYAngle(),0,0,1);
	  drawColor(pCar.gun);
		glPushMatrix();
			glTranslatef(0, 0, pCar.body.getZLength()/2 );
	  	drawEllipse3d(pCar.body.getXLength()/4, pCar.body.getYLength()/4);
		glPopMatrix();
	  drawRectangle3d(pCar.body);
	  glPushMatrix();
	  	glTranslatef(0, 0, -pCar.body.getZLength()/4.5);
	  	drawWheels(pCar);
	  glPopMatrix();
	  drawGun(pCar);
	glPopMatrix();
}

void drawWheels(Car pCar) {
	GLfloat lHubX = (pCar.body.getXLength()/2)*0.7;
	GLfloat lHubY = (pCar.body.getYLength()/2) + (pCar.hub.getXLength()/2);
	GLfloat lWheelX = lHubX;
	GLfloat lWheelY = lHubY + (pCar.hub.getXLength()/2) + (pCar.wheel.getXLength()/2);

	// front

	glPushMatrix();
		glTranslatef(lHubX,lHubY,0);
		glRotatef(90,0,0,1);
		pCar.hub.setXYPosition(0,0);
		drawCylinder(pCar.hub);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(lWheelX,lWheelY,0);
		glRotatef(90,0,0,1);
		glRotatef(pCar.getDegreeSteeringAngle(),0,0,1);
		pCar.wheel.setXYPosition(0,0);
		drawCylinder(pCar.wheel);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(lHubX,-lHubY,0);
		glRotatef(90,0,0,1);
		pCar.hub.setXYPosition(0,0);
		drawCylinder(pCar.hub);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(lWheelX,-lWheelY,0);
		glRotatef(90,0,0,1);
		glRotatef(pCar.getDegreeSteeringAngle(),0,0,1);
		pCar.wheel.setXYPosition(0,0);
		drawCylinder(pCar.wheel);
	glPopMatrix();

	// rear
	glPushMatrix();
		glTranslatef(-lHubX,lHubY,0);
		glRotatef(90,0,0,1);
		pCar.hub.setXYPosition(0,0);
		drawCylinder(pCar.hub);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-lWheelX,lWheelY,0);
		glRotatef(90,0,0,1);
		pCar.wheel.setXYPosition(0,0);
		drawCylinder(pCar.wheel);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-lHubX,-lHubY,0);
		glRotatef(90,0,0,1);
		pCar.hub.setXYPosition(0,0);
		drawCylinder(pCar.hub);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-lWheelX,-lWheelY,0);
		glRotatef(90,0,0,1);
		pCar.wheel.setXYPosition(0,0);
		drawCylinder(pCar.wheel);
	glPopMatrix();
}

void drawGun(Car pCar) {
	glPushMatrix();
		glTranslatef(pCar.body.getXLength()/2,0,0);
	  glRotatef(pCar.getDegreeGunXYAngle(),0,0,1);
	  glRotatef(-pCar.getDegreeGunXZAngle(),0,1,0);
		glTranslatef(pCar.gun.getXLength()/2,0,0);
		pCar.gun.setXYPosition(0,0);
		drawCylinder(pCar.gun);
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

void drawEllipse3d(GLfloat radiusX, GLfloat radiusY) {
	glPushMatrix();
		glScalef( radiusX, radiusY, radiusY);
    glutSolidSphere(1, 100, 16);
	glPopMatrix();
}

void drawCylinder(Cylinder pCylinder) {
	if (!pCylinder.getVisible())
		return;
	Circle lCircle;
	GLfloat lRadius = pCylinder.getRadius();
	lCircle.setRadius( lRadius);
	GLfloat lXLength = pCylinder.getXLength();
	Rectangle lRec;
	lRec.setXLength( lXLength);
	lRec.setYLength( lRadius * 2 * M_PI / 36);
	GLfloat lR = pCylinder.getR();
	GLfloat lG = pCylinder.getG();
	GLfloat lB = pCylinder.getB();
	lCircle.setRGB(lR,lG,lB);
	lRec.setRGB(lR,lG,lB);
	glPushMatrix();
		glPushMatrix();
			glRotatef(90, 0, 1, 0);
			glTranslatef(0, 0, lXLength/2);
			draw(lCircle);
		glPopMatrix();

		glPushMatrix();
			glRotatef(-90, 0, 1, 0);
			glTranslatef(0, 0, lXLength/2);
			draw(lCircle);
		glPopMatrix();


    glPushMatrix();
      for (int i = 0; i <= 36; ++i) {
        glRotatef(10,1,0,0);

	      glPushMatrix();
	        glTranslatef(0,0,lRadius);
	        draw(lRec);
	      glPopMatrix();
      }
		glPopMatrix();

	glPopMatrix();
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
				char lString[20];
				if (pWin) {
					sprintf(lString, "You win! :)");
	      	glColor3f(0,1,0);
					glRasterPos2f(0.45, 0.5);
					}
				else {
					sprintf(lString, "You lose! :(");
	      	glColor3f(1,0,0);
					glRasterPos2f(0.43, 0.5);
					}
				for (int i = 0; lString[i]; ++i) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, lString[i]);
				}
		  glPopAttrib();
	  glPopMatrix();
	  glMatrixMode (GL_MODELVIEW);
  glPopMatrix();
}

void setThirdPersonCamera(Car pPlayerCar, GLfloat pXYDegreeAngle, GLfloat pXZDegreeAngle) {
	GLfloat lXYAngle = M_PI * pXYDegreeAngle / 180;
	GLfloat lXZAngle = M_PI * pXZDegreeAngle / 180;
	GLfloat lRadius = pPlayerCar.getRadius();
	gluLookAt(pPlayerCar.getX() + lRadius * 5 * cos(lXYAngle) * cos(lXZAngle),
						pPlayerCar.getY() + lRadius * 5 * sin(lXYAngle) * cos(lXZAngle),
						lRadius * 5 * sin(lXZAngle),
						pPlayerCar.getX(),pPlayerCar.getY(),0,0,0,1);
}

void setCockpitCamera(Car pPlayerCar) {
	GLfloat lXYAngle = (pPlayerCar.getDegreeXYAngle() ) * M_PI / 180;
	GLfloat lXZAngle = (pPlayerCar.getDegreeXZAngle() ) * M_PI / 180;
	GLfloat lZPosition = pPlayerCar.getRadius() * 0.7 + pPlayerCar.getZ();
	gluLookAt(pPlayerCar.getX(), pPlayerCar.getY(), lZPosition,
						pPlayerCar.getX() + cos(lXYAngle) * cos(lXZAngle), pPlayerCar.getY() + sin(lXYAngle) * cos(lXZAngle), lZPosition + sin(lXZAngle),0,0,1);

}

void setGunCamera(Car pPlayerCar) {
	GLfloat lXYAngle = (pPlayerCar.getDegreeXYAngle() + pPlayerCar.getDegreeGunXYAngle()) * M_PI / 180;
	GLfloat lXZAngle = (pPlayerCar.getDegreeXZAngle() + pPlayerCar.getDegreeGunXZAngle()) * M_PI / 180;
}
