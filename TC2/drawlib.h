#ifndef DRAWLIB
#define DRAWLIB
#include <GL/glut.h>
#include "classlib.h"

void drawColor(Object pObject);

void draw(Rectangle pRectangle, GLsizei pWindowW, GLsizei pWindowH);

void draw(Circle pCircle, GLsizei pWindowW, GLsizei pWindowH);

#endif