#include "callbacklib.h"

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);   
	draw(gOuterCircle);
	draw(gInnerCircle);
	draw(gStripeRect);
	draw(gEnemyCircle1);
	draw(gEnemyCircle2);
	draw(gEnemyCircle3);
	draw(gPlayerCircle);
	glutSwapBuffers();
}

void keyPress(unsigned char key, int x, int y){
switch (key)
	{
		case 'w':
		case 'W':
			gKeyboardStatus[(int)('w')] = true;
			break;
		case 's':
		case 'S':
			gKeyboardStatus[(int)('s')] = true;
			break;
		case 'a':
		case 'A':
			gKeyboardStatus[(int)('a')] = true;
			break;
		case 'd':
		case 'D':
			gKeyboardStatus[(int)('d')] = true;
			break;
	}
}

void keyUp(unsigned char key, int x, int y){
	switch (key)
	{
		case 'w':
		case 'W':
			gKeyboardStatus[(int)('w')] = false;
			break;
		case 's':
		case 'S':
			gKeyboardStatus[(int)('s')] = false;
			break;
		case 'a':
		case 'A':
			gKeyboardStatus[(int)('a')] = false;
			break;
		case 'd':
		case 'D':
			gKeyboardStatus[(int)('d')] = false;
			break;
	}
}

void idle(void){
	static GLdouble lPreviousTime = 0;
	GLdouble lCurrentTime;
	GLdouble lTimeDifference;

	// Elapsed time from the initiation of the game.
	lCurrentTime = glutGet(GLUT_ELAPSED_TIME);
	lTimeDifference = lCurrentTime - lPreviousTime; // Elapsed time from the previous frame.
	lPreviousTime = lCurrentTime; //Update previous time
		
	Circle lNewCircle = MoveCircle(gPlayerCircle, lTimeDifference, gSpeed);

	if( !(CirclesColliding(lNewCircle,gInnerCircle) or CirclesColliding(lNewCircle,gEnemyCircle1) 
				or CirclesColliding(lNewCircle,gEnemyCircle2) or CirclesColliding(lNewCircle,gEnemyCircle3)
				or !CircleCovered(lNewCircle, gOuterCircle)) )
		gPlayerCircle = lNewCircle;

	glutPostRedisplay();
}

bool CirclesColliding (Circle pCircle1, Circle pCircle2) {
	GLfloat lDeltaX = pCircle1.getX() - pCircle2.getX();
	GLfloat lDeltaY = pCircle1.getY() - pCircle2.getY();
	GLfloat lRadiusSum = pCircle1.getRadius() + pCircle2.getRadius();
	return (lRadiusSum > sqrt(lDeltaX*lDeltaX + lDeltaY*lDeltaY));
}

bool CircleCovered(Circle pInnerCircle, Circle pOuterCircle) {
	GLfloat lDeltaX = pInnerCircle.getX() - pOuterCircle.getX();
	GLfloat lDeltaY = pInnerCircle.getY() - pOuterCircle.getY();
	GLfloat lMaximumDistance = pOuterCircle.getRadius() - pInnerCircle.getRadius();
	return (lMaximumDistance > sqrt(lDeltaX*lDeltaX + lDeltaY*lDeltaY));
}

Circle MoveCircle(Circle pCircle, GLdouble timeDiff , GLdouble pSpeed ) {
	if (gKeyboardStatus[(int)('w')])
		pCircle.incY(pSpeed * timeDiff);
	if (gKeyboardStatus[(int)('s')])
		pCircle.incY(-pSpeed * timeDiff);
	if (gKeyboardStatus[(int)('a')])
		pCircle.incX(-pSpeed * timeDiff);
	if (gKeyboardStatus[(int)('d')])
		pCircle.incX(pSpeed * timeDiff);
	return pCircle;
}