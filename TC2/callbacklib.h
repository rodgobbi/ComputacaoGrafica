#ifndef CALLBACKLIB
#define CALLBACKLIB
#include <GL/glut.h>
#include "classlib.h"
#include "drawlib.h"
#include <cmath>

extern Circle gOuterCircle, gInnerCircle, gEnemyCircle1, gEnemyCircle2, gEnemyCircle3, gPlayerCircle;
extern Rectangle gStripeRect;
extern bool gKeyboardStatus[256];
extern GLfloat gSpeed;

void display(void);
void keyPress(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void idle(void);
bool CirclesColliding (Circle pCircle1, Circle pCircle2);
bool CircleCovered(Circle pInnerCircle, Circle pOuterCircle);
Circle MoveCircle(Circle pCircle, GLdouble timeDiff , GLdouble pSpeed ) ;

#endif