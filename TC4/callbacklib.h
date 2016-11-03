#ifndef CALLBACKLIB
#define CALLBACKLIB
#include <GL/glut.h>
#include "classlib.h"
#include "drawlib.h"
#include "enginelib.h"
#include <list>
using namespace std;

extern GLsizei gWindowWidth, gWindowHeight;
extern GLint gLastPointerX, gLastPointerY;
extern Circle gOuterCircle, gInnerCircle;
extern Car gPlayerCar;
extern Rectangle gStripeRect;
extern bool gKeyboardStatus[256], gCompletedQuarter[4];
extern GLfloat gMovementSpeed, gRotationSpeed, gShotSpeed, gEnemyMovementSpeed, gEnemyRotationSpeed, gEnemyShotSpeed, gEnemyShotFrequency;
extern list<Car> gEnemiesList;
extern list<Circle> gShotsList, gEnemyShotsList;
extern GLdouble gStartTime;

void display(void);
void keyPress(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void idle(void);
void mouseClick(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void drawTime(GLdouble pMilisecTime);

#endif