#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

#define paddleHeight 80
#define paddleWidth 10
#define baseHeight 40
#define baseWidth 100
#define radiusWheel 30
#define zAxis 0

GLfloat gx = 0.0, gy = 0.0, gtetaR = 0.0, gteta1 = 0, gteta2 = 0, gteta3 = 0;

bool gKeyboard[4];

void drawRect(int w, int h,  float r, float g, float b) {

  glColor3f(r,g,b);

	glBegin(GL_QUADS);
		glVertex2f( -w/2.0, 0.0);
		glVertex2f(-w/2.0,h);
		glVertex2f(w/2.0,h);
		glVertex2f(w/2.0,0.0);
	glEnd();
}

void drawArm(float x, float y, float teta1, float teta2, float teta3) {
  glPushMatrix();

  glTranslatef(x,y,0);
  glRotatef(teta1,0,0,1);

  drawRect(paddleWidth, paddleHeight, 0, 0, 1);

  glTranslatef(0,paddleHeight,0);
  glRotatef(teta2,0,0,1);

  drawRect(paddleWidth, paddleHeight, 0, 1, 1);

  glTranslatef(0,paddleHeight,0);
  glRotatef(teta3,0,0,1);

  drawRect(paddleWidth, paddleHeight, 0, 1, 0);

  glPopMatrix();

}

void drawCircle(float radius, float r, float g, float b) {
  float x, y;
  glColor3f(r,g,b);
  glPointSize(3);
  glBegin(GL_POINTS);
    for (int i = 0; i < 360; i = i + 20 ) {
      x = radius * cos(M_PI*i/180);
      y = radius * sin(M_PI*i/180);
      glVertex3f(x,y,0);
    }
  glEnd();
}


void drawRobot(int x, int y, float tetaR, float teta1,  float teta2, float teta3) {

  glPushMatrix();

  glTranslatef(gx,gy,0);

  drawRect(baseWidth, baseHeight, 1.0, 0.0, 0.0 );

  glPushMatrix();
  glTranslatef(-baseWidth/2,0,0);
  glRotatef(tetaR,0,0,1);
  drawCircle(radiusWheel, 0, 1, 1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(baseWidth/2,0,0);
  glRotatef(tetaR,0,0,1);
  drawCircle(radiusWheel, 0, 1, 1);
  glPopMatrix();

  drawArm(0, baseHeight, gteta1,gteta2,gteta3);

  glPopMatrix();
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);

  drawRobot(0,0, gtetaR ,0,0,0);

	glutSwapBuffers();
}

void init(void){
	glClearColor(0.0,0.0,0.0,0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-250,250,-250,250,-100,100);
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
    case 'u':
    case 'U':
      gteta1 += 1;
      break;
    case 'j':
    case 'J':
      gteta1 -= 1;
      break;
    case 'i':
    case 'I':
      gteta2 += 1;
      break;
    case 'k':
    case 'K':
      gteta2 -= 1;
      break;
    case 'o':
    case 'O':
      gteta3 += 1;
      break;
    case 'l':
    case 'L':
      gteta3 -= 1;
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

void moveY(float Y) {
  gy = gy + Y;
}

void moveX(float X) {
  gx = gx + X;
  gtetaR = gtetaR - X * 5 * ( 2 * M_PI)/ radiusWheel;
}

void idle(void){
	if (gKeyboard[0])
		moveY(1);
	if (gKeyboard[1])
		moveY(-1);
	if (gKeyboard[2])
		moveX(-1);
	if (gKeyboard[3])
		moveX(1);

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
	printf("passou aqui x = %f y = %f \n", x/250.0 , (250 - y)/250.0 );
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700,700);
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
