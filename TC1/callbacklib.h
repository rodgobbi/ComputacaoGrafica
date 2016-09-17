#ifndef CALLBACKLIB
#define CALLBACKLIB
#include <GL/glut.h>
#include "classlib.h"
#include "drawlib.h"

extern Square gSquare;
extern GLsizei gWindowWidth, gWindowHeight, gLastPointerX, gLastPointerY;
extern bool gLeftClickInside;

void display(void);

void mouseClick(int button, int state, int x, int y);

void mouseMotion(int x, int y);

#endif