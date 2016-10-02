#ifndef CALLBACKLIB
#define CALLBACKLIB
#include <GL/glut.h>
#include "classlib.h"
#include "drawlib.h"

extern GLsizei gWindowWidth, gWindowHeight;
extern Circle gOuterCircle, gInnerCircle, gEnemyCircle1, gEnemyCircle2, gEnemyCircle3, gPlayerCircle;
extern Rectangle gStripeRect;
extern bool gKeyboardDown[4];

void display(void);
void keyPress(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void idle(void);

#endif