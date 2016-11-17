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
extern bool gKeyboardStatus[256], gCompletedQuarter[4], gGameOver, gRightClickDown;
extern GLfloat gMovementSpeed, gRotationSpeed, gShotSpeed, gEnemyMovementSpeed, gEnemyRotationSpeed, gEnemyShotSpeed, gEnemyShotFrequency;
extern GLfloat gCameraXYAngle, gCameraXZAngle;
extern list<Car> gEnemiesList;
extern list<Circle> gShotsList, gEnemyShotsList;
extern list<Controller> gControllersList;
extern GLdouble gStartTime;

void display(void);
void keyPress(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void idle(void);
void mouseClick(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void mouseClick(int button, int state, int x, int y);
void CheckGameOverAndDraw();
void MoveEnemies(GLdouble timeDiff);
bool Colliding(Controller *pController, Car pNewCar);
void setCamera();

#endif
