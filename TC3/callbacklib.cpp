#include "callbacklib.h"

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	draw(gOuterCircle);
	draw(gInnerCircle);
	draw(gStripeRect);
	for (list<Circle>::iterator it = gEnemiesList.begin(); it != gEnemiesList.end(); it++)
		draw( (Circle) *it );
	draw( (Circle) gPlayerCar);
	draw(gPlayerCar);
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

	gPlayerCar = SteerCarWheels(gPlayerCar, lTimeDifference, gRotationSpeed);

	gPlayerCar = RotateCar(gPlayerCar, lTimeDifference, gRotationSpeed);

	Car lNewCar = MoveCar(gPlayerCar, lTimeDifference, gMovementSpeed);

	// True if not colliding with anything
	if( !(CirclesColliding(lNewCar,gInnerCircle) or CirclesColliding(lNewCar,gEnemiesList) or !CircleCovered(lNewCar, gOuterCircle)) )
		gPlayerCar = lNewCar;

	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y){
	// if (( button == GLUT_LEFT_BUTTON) ) {
	// 	if (state == GLUT_DOWN) {
	// 		if (!gSquare.getVisible()) {
	// 			gSquare.setVisible( true );
	// 			gSquare.setPosition(x, gWindowHeight - y);
	// 		}
	// 		if (gSquare.getVisible() and gSquare.pointIsInside(x,gWindowHeight - y) ) {
	// 			gLeftClickInside = true;
	// 			gLastPointerX = x;
	// 			gLastPointerY = gWindowHeight - y;
	// 		}
	// 	}
	// 	else if (state == GLUT_UP)
	// 		gLeftClickInside = false;
	// } 
	// else if (( button == GLUT_RIGHT_BUTTON) and (state == GLUT_DOWN)) {
	// 	if (gSquare.pointIsInside(x,gWindowHeight - y))
	// 		gSquare.setVisible(false);
	// }

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
