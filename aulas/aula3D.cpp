#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

void init(void) {
  glClearColor(0,0,0,0);
  glShadeModel(GL_FLAT);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
}

void DrawObj(double size) {
  GLfloat materialEmission[] = {0,0,0,1};
  GLfloat materialColor[] = {0,0,1,1};
  GLfloat materialColorAMB[] = {1,1,0,1};
  GLfloat mat_specular[] = {1,1,1,1};
  GLfloat mat_shininess[] = {128};
  glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission );
  glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glColor3f(1,0,0);
  // glutSolidSphere(size, 100, 16);
  glutSolidCube(size);
}

void DrawAxes(double size) {
  GLfloat mat_ambient_r[] = {1,0,0,1};
  GLfloat mat_ambient_g[] = {0,1,0,1};
  GLfloat mat_ambient_b[] = {0,0,1,1};
  GLfloat no_mat[] = {0,0,0,1};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, no_mat);
  glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);

  // x axis
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_r);
    glColor3fv(mat_ambient_g);
    glScalef(size, size*0.1, size*0.1);
    glTranslatef(0.5,0,0); // put in one end
    glutSolidCube(1.0);
  glPopMatrix();

  // y axis
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_g);
    glColor3fv(mat_ambient_b);
    glRotatef(90,0,0,1);
    glScalef(size, size*0.1, size*0.1);
    glTranslatef(0.5,0,0);
    glutSolidCube(1.0);
  glPopMatrix();

  // z axis
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_b);
    glColor3fv(mat_ambient_r);
    glRotatef(-90,0,1,0);
    glScalef(size, size*0.1, size*0.1);
    glTranslatef(0.5,0,0);
    glutSolidCube(1.0);
  glPopMatrix();
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  GLfloat light_position[] = {0,5,2,1};
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  DrawAxes(1.5);

  DrawObj(1);

  glutSwapBuffers();
}

void idle(void ) {
  glutPostRedisplay();
}

void reshape(int w, int h) {
  glViewport (0,0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w <= h)
    gluPerspective(90, (GLfloat)h /  (GLfloat)w, 2, 15);
  else
    gluPerspective(90, (GLfloat)w /  (GLfloat)h, 2, 15);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(2,2,5,0,0,0,0,1,0);
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Hello");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
  glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}
