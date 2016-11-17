#include "callbacklib.h"

void display(void){
	if (gGameOver)
		return;
  glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
	ChooseCamera();
	glPushMatrix();
	  // GLfloat light_position[] = {0, 0, 100, 1};

		if (gKeyboardStatus[(int)('n')])
			TurnOnCarLight(gPlayerCar);
		else {
			TurnOnTrackLight(gOuterCircle);
		}
	  if (gKeyboardStatus[(int)('l')])
	  	glDisable(GL_LIGHTING);
	  else {
	    glEnable(GL_LIGHTING);
	  }
		drawFlatSphere(gOuterCircle);
		glPushMatrix();
			glTranslatef(0,0,1);
			draw(gInnerCircle);
			draw(gStripeRect);
		glPopMatrix();
		for (list<Car>::iterator it = gEnemiesList.begin(); it != gEnemiesList.end(); it++)
			draw( *it );
		for (list<Circle>::iterator it = gShotsList.begin(); it != gShotsList.end(); it++)
			drawSphere( *it );
		for (list<Circle>::iterator it = gEnemyShotsList.begin(); it != gEnemyShotsList.end(); it++)
			drawSphere( *it );
		draw(gPlayerCar);
		if (gStartTime > 0)
			drawTime(gOuterCircle, glutGet(GLUT_ELAPSED_TIME) - gStartTime);
		else
			drawTime(gOuterCircle, 0);
		CheckGameOverAndDraw();
	glPopMatrix();
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
		case 'n':
		case 'N':
			gKeyboardStatus[(int)('n')] = !gKeyboardStatus[(int)('n')];
			break;
		case 'l':
		case 'L':
			gKeyboardStatus[(int)('l')] = !gKeyboardStatus[(int)('l')];
			break;
		case '1':
		case '!':
			gKeyboardStatus[(int)('1')] = true;
			gKeyboardStatus[(int)('2')] = false;
			gKeyboardStatus[(int)('3')] = false;
			break;
		case '2':
		case '@':
			gKeyboardStatus[(int)('1')] = false;
			gKeyboardStatus[(int)('2')] = true;
			gKeyboardStatus[(int)('3')] = false;
			break;
		case '3':
		case '#':
			gKeyboardStatus[(int)('1')] = false;
			gKeyboardStatus[(int)('2')] = false;
			gKeyboardStatus[(int)('3')] = true;
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

	if (gGameOver)
		return;

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

	MoveEnemies(lTimeDifference);

	MoveShots(gShotsList, lTimeDifference, gShotSpeed, gOuterCircle);

	MoveShots(gEnemyShotsList, lTimeDifference, gEnemyShotSpeed, gOuterCircle);

	EnemyCarsShot(gEnemiesList, gEnemyShotsList, lTimeDifference, gEnemyShotFrequency);

	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y){
	if (( button == GLUT_LEFT_BUTTON) ) {
		if (state == GLUT_DOWN) {
			gShotsList.push_back( CarShot(gPlayerCar) );
		}
	}
	else if (( button == GLUT_RIGHT_BUTTON) ) {
			if (state == GLUT_DOWN)
				gRightClickDown = true;
			else if (state == GLUT_UP)
				gRightClickDown = false;
		}

	glutPostRedisplay();
}

void mouseMotion(int x, int y) {
	GLint lNewPointerX = x;
	GLint lNewPointerY = gWindowHeight - y;
	if (gRightClickDown) {
		gCameraXYAngle -=  lNewPointerX - gLastPointerX;
		gCameraXZAngle -= lNewPointerY - gLastPointerY;
		if (gCameraXZAngle < 5)
			gCameraXZAngle = 5;
		else if (gCameraXZAngle > 89)
			gCameraXZAngle = 89;
	}
	else {
		gPlayerCar.incGunXYAngle( gLastPointerX - lNewPointerX);
		gPlayerCar.incGunXZAngle( lNewPointerY - gLastPointerY);
	}
	gLastPointerX = lNewPointerX;
	gLastPointerY = lNewPointerY;
	glutPostRedisplay();
}

void CheckGameOverAndDraw() {
	if (gCompletedQuarter[3])	{
		gGameOver = true;
		drawGameOver(gOuterCircle, true);
	}
	else if (ShotsColliding(gPlayerCar,gEnemyShotsList)) {
		gGameOver = true;
		drawGameOver(gOuterCircle, false);
	}
}

void MoveEnemies(GLdouble timeDiff) {
	Car lNewCar;
	list<Car>::iterator it2;
	list<Controller>::iterator it = gControllersList.begin();
	while ( it != gControllersList.end() ) {
		if (ShotsColliding( *((*it).getCar()), gShotsList)) {
			it2 = gEnemiesList.begin();
			while ( it2 != gEnemiesList.end()) {
				if ( &(*it2) == (*it).getCar()) {
					it2 = gEnemiesList.erase(it2);
					it = gControllersList.erase(it);
					break;
				}
				else
					it2++;
			}
		}
		else {
			if ( !(*it).foward) {
				lNewCar = MoveObject( *((*it).getCar()), timeDiff, - gEnemyMovementSpeed );
				lNewCar.setSteeringAngle(0);
				if (Colliding( &(*it), lNewCar ) or ((*it).movTime < 0)) {
					(*it).foward = true;
					(*it).turning = true;
					(*it).movTime = 500;
				}
				else {
					*((*it).getCar()) = lNewCar;
					(*it).movTime -= timeDiff;
				}
			}
			else {
				if ( !(*it).turning ) {
					lNewCar = MoveObject( *((*it).getCar()), timeDiff, gEnemyMovementSpeed );
					lNewCar.setSteeringAngle(0);
					if (Colliding( &(*it), lNewCar )) {
						(*it).foward = false;
						(*it).movTime = 1000;
						(*it).turnLeft = !(*it).turnLeft;
					}
					else if (((*it).movTime < 0)) {
						(*it).foward = true;
						(*it).turning = true;
						(*it).movTime = 200;
					}
					else {
						*((*it).getCar()) = lNewCar;
						(*it).movTime -= timeDiff;
					}
				}
				else {
					lNewCar = *((*it).getCar());
					if ( (*it).turnLeft) {
						lNewCar.incXYAngle(timeDiff * gEnemyRotationSpeed);
						lNewCar.setSteeringAngle(timeDiff * gEnemyRotationSpeed * 10);
					}
					else {
						lNewCar.incXYAngle(-timeDiff * gEnemyRotationSpeed);
						lNewCar.setSteeringAngle(-timeDiff * gEnemyRotationSpeed * 10);
					}
					lNewCar = MoveObject( lNewCar, timeDiff, gEnemyMovementSpeed );
					if (Colliding( &(*it), lNewCar )) {
						(*it).foward = false;
						(*it).movTime = 1000;
						(*it).turnLeft = !(*it).turnLeft;
					}
					else if (((*it).movTime < 0)) {
						(*it).foward = true;
						(*it).turning = false;
						(*it).movTime = 500;
					}
					else {
						*((*it).getCar()) = lNewCar;
						(*it).movTime -= timeDiff;
					}
				}
			}
			it++;
		}
	}
}

bool Colliding(Controller *pController, Car pNewCar) {
	for (list<Controller>::iterator it = gControllersList.begin(); it != gControllersList.end(); it++)
		if ( pController != &(*it))
			if ( CirclesColliding( pNewCar, *((*it).getCar()) ) )
				return true;
	if (CirclesColliding(pNewCar, gInnerCircle))
		return true;
	if ( !CircleCovered(pNewCar, gOuterCircle))
		return true;
	if ( CirclesColliding(pNewCar, gPlayerCar))
		return true;
	return false;
}

void ChooseCamera() {
	if (gKeyboardStatus[(int)('1')] == true) {
		setCockpitCamera(gPlayerCar);
	}
	else if (gKeyboardStatus[(int)('2')] == true) {
		setGunCamera(gPlayerCar);
	}
	else {
		setThirdPersonCamera(gPlayerCar, gCameraXYAngle, gCameraXZAngle);
	}
}
