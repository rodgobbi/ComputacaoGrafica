#include "callbacklib.h"

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	draw(gOuterCircle);
	draw(gInnerCircle);
	draw(gStripeRect);
	for (list<Car>::iterator it = gEnemiesList.begin(); it != gEnemiesList.end(); it++)
		draw( *it );
	for (list<Circle>::iterator it = gShotsList.begin(); it != gShotsList.end(); it++)
		draw( *it );
	for (list<Circle>::iterator it = gEnemyShotsList.begin(); it != gEnemyShotsList.end(); it++)
		draw( *it );
	draw(gPlayerCar);
	if (gStartTime > 0)
		drawTime(glutGet(GLUT_ELAPSED_TIME) - gStartTime, gWindowWidth, gWindowHeight);
	glutSwapBuffers();
}

void keyPress(unsigned char key, int x, int y){
switch (key)
	{
		case 'w':
		case 'W':
			gKeyboardStatus[(int)('w')] = true;
			if (gStartTime == 0)
				gStartTime = glutGet(GLUT_ELAPSED_TIME);
			break;
		case 's':
		case 'S':
			gKeyboardStatus[(int)('s')] = true;
			if (gStartTime == 0)
				gStartTime = glutGet(GLUT_ELAPSED_TIME);
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

	gPlayerCar = SteerCarWheels(gPlayerCar, lTimeDifference, gRotationSpeed);

	Car lNewCar = RotateCar(gPlayerCar, lTimeDifference, gRotationSpeed);

	lNewCar = MoveCar(lNewCar, lTimeDifference, gMovementSpeed);

	// True if not colliding with anything
	if( !(CirclesColliding(lNewCar,gInnerCircle) or CirclesColliding(lNewCar,gEnemiesList) 
			or !CircleCovered(lNewCar, gOuterCircle)) ) {
		CheckCompletedQuarter(lNewCar, gPlayerCar, gOuterCircle, gCompletedQuarter);
		gPlayerCar = lNewCar;
	}

	MoveShots(gShotsList, lTimeDifference, gShotSpeed, gOuterCircle);

	MoveShots(gEnemyShotsList, lTimeDifference, gShotSpeed, gOuterCircle);

	EnemyCarsShot(gEnemiesList, gEnemyShotsList, lTimeDifference, gEnemyShotFrequency);

	if( gCompletedQuarter[2] and gCompletedQuarter[3])
		throw string("Birrrrrr!");
	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y){
	if (( button == GLUT_LEFT_BUTTON) ) {
		if (state == GLUT_DOWN) {
			gShotsList.push_back( CarShot(gPlayerCar) );
		}
	}

	glutPostRedisplay();
}

void mouseMotion(int x, int y) {
	GLint lNewPointerX = x;
	GLint lNewPointerY = gWindowHeight - y;
	gPlayerCar.incGunDirectionAngle( gLastPointerX - lNewPointerX);
	gLastPointerX = lNewPointerX;
	gLastPointerY = lNewPointerY;
	glutPostRedisplay();
}
