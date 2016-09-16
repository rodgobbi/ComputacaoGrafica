#include "callbacklib.h"

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);   
	draw(gSquare, gWindowWidth, gWindowHeight);
	glutSwapBuffers();
}

void mouseClick(int button, int state, int x, int y){
	if (( button == GLUT_LEFT_BUTTON) ) {
		if (state == GLUT_DOWN) {
			if (!gSquare.getVisible()) {
				gSquare.setVisible( true );
				gSquare.setPosition(x, gWindowHeight - y);
			}
			if (gSquare.getVisible() and gSquare.pointIsInside(x,gWindowHeight - y) )
				gLeftClickInside = true;
		}
		else if (state == GLUT_UP)
			gLeftClickInside = false;
	} 
	else if (( button == GLUT_RIGHT_BUTTON) and (state == GLUT_DOWN)) {
		gSquare.setVisible(false);
	}

	glutPostRedisplay();
}

void mouseMotion(int x, int y) {
	if (gLeftClickInside) {
		gSquare.setPosition(x, gWindowHeight - y);	
		glutPostRedisplay();
	}
}