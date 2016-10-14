#ifndef CALLBACKLIB
#define CALLBACKLIB
#include <GL/glut.h>
#include "classlib.h"
#include "drawlib.h"
#include "enginelib.h"
#include <list>
using namespace std;

extern Circle gOuterCircle, gInnerCircle;
extern Car gPlayerCar;
extern Rectangle gStripeRect;
extern bool gKeyboardStatus[256];
extern GLfloat gMovementSpeed, gRotationSpeed;
extern list<Circle> gEnemiesList;

void display(void);
void keyPress(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void idle(void);

#endif
