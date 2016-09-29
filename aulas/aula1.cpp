#include <GL/glut.h>
#include <stdio.h>

GLfloat gx = 0.0, gy = 0.0;

bool gKeyboard[4];

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
		glVertex3f(0.25 + gx,0.25 + gy,0.0);    
		glVertex3f(0.75 + gx,0.25 + gy,0.0);    
		glVertex3f(0.75 + gx,0.75 + gy,0.0);    
		glVertex3f(0.25 + gx,0.75 + gy,0.0);
	glEnd();    

	glutSwapBuffers();
}

void init(void){
	glClearColor(0.0,0.0,0.0,0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
}
void keyPress(unsigned char key, int x, int y){
	switch (key)
	{
		case 'w':
		case 'W':
			gKeyboard[0] = 1;
			break;
		case 's':
		case 'S':
			gKeyboard[1] = 1;
			break;
		case 'a':
		case 'A':
			gKeyboard[2] = 1;
			break;
		case 'd':
		case 'D':
			gKeyboard[3] = 1;
			break;
	}
}

void keyUp(unsigned char key, int x, int y){
	switch (key)
	{
		case 'w':
		case 'W':
			gKeyboard[0] = 0;
			break;
		case 's':
		case 'S':
			gKeyboard[1] = 0;
			break;
		case 'a':
		case 'A':
			gKeyboard[2] = 0;
			break;
		case 'd':
		case 'D':
			gKeyboard[3] = 0;
			break;
	}
}

void idle(void){
	if (gKeyboard[0])
		gy = gy + 0.01;
	if (gKeyboard[1])
		gy = gy - 0.01;
	if (gKeyboard[2])
		gx = gx - 0.01;
	if (gKeyboard[3])
		gx = gx + 0.01;

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
	printf("passou aqui x = %f y = %f \n", x/250.0 , (250 - y)/250.0 );
}

int main(int argc, char** argv)
{    
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(250,250);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Hello");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyUp);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutMainLoop();

	return 0;
}