#include "callbacklib.h"

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);   
	draw(gOuterCircle, gWindowWidth, gWindowHeight);
	draw(gInnerCircle, gWindowWidth, gWindowHeight);
	draw(gStripeRect, gWindowWidth, gWindowHeight);
	draw(gEnemyCircle1, gWindowWidth, gWindowHeight);
	draw(gEnemyCircle2, gWindowWidth, gWindowHeight);
	draw(gEnemyCircle3, gWindowWidth, gWindowHeight);
	draw(gPlayerCircle, gWindowWidth, gWindowHeight);
	glutSwapBuffers();
}

void keyPress(unsigned char key, int x, int y){
	switch (key)
	{
		case 'w':
		case 'W':
			gKeyboardDown[0] = true;
			break;
		case 's':
		case 'S':
			gKeyboardDown[1] = true;
			break;
		case 'a':
		case 'A':
			gKeyboardDown[2] = true;
			break;
		case 'd':
		case 'D':
			gKeyboardDown[3] = true;
			break;
	}
}

void keyUp(unsigned char key, int x, int y){
	switch (key)
	{
		case 'w':
		case 'W':
			gKeyboardDown[0] = false;
			break;
		case 's':
		case 'S':
			gKeyboardDown[1] = false;
			break;
		case 'a':
		case 'A':
			gKeyboardDown[2] = false;
			break;
		case 'd':
		case 'D':
			gKeyboardDown[3] = false;
			break;
	}
}

void idle(void){
	if (gKeyboardDown[0])
		gPlayerCircle.incY(1);
	if (gKeyboardDown[1])
		gPlayerCircle.incY(-1);
	if (gKeyboardDown[2])
		gPlayerCircle.incX(-1);
	if (gKeyboardDown[3])
		gPlayerCircle.incX(1);

	glutPostRedisplay();
}