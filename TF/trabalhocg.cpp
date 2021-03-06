#include <string.h>
#include <iostream>
#include <list>
using namespace std;
#include <GL/glut.h>
#include "tinyxml.h"
#include "classlib.h"
#include "drawlib.h"
#include "callbacklib.h"

string ExtractConfigData(string pConfigFilePath);
void CreateWindow(string pFilePath, GLsizei& pWindowWidth, GLsizei& pWindowHeight);
Circle ExtractCircleData(TiXmlElement* pElement);
Car ExtractCarData(TiXmlElement* pElement);
Rectangle ExtractRectData(TiXmlElement* pElement);
void ExtractCircuitData(TiXmlElement* pElement);
void ExtractNodeData(TiXmlNode* pNode);
Car PaintPlayerCar(Car pCar);
Car PaintEnemyCar(Car pCar);
void ConvertCoordinates(Circle pReferenceCircle);
void setCarControllers();

GLsizei gWindowWidth, gWindowHeight;
GLint gLastPointerX, gLastPointerY;
Circle gOuterCircle, gInnerCircle;
Car gPlayerCar;
Rectangle gStripeRect;
list<Car> gEnemiesList;
list<Circle> gShotsList, gEnemyShotsList;
list<Controller> gControllersList;
bool gKeyboardStatus[256], gCompletedQuarter[4], gGameOver = false, gRightClickDown = false;
GLfloat gMovementSpeed = 0, gRotationSpeed = 0.1, gShotSpeed = 0, gEnemyMovementSpeed = 0, gEnemyRotationSpeed = 0.1, gEnemyShotSpeed = 0, gEnemyShotFrequency = 0;
GLfloat gCameraXYAngle = -90, gCameraXZAngle = 45;
GLdouble gStartTime = 0;

int main(int argc, char** argv)
{
	try {
		if (argc != 2) {
			throw string("Número de argumentos inválido. É necessário informar o diretório do arquivo config.xml, e apenas este argumento.");
		}
		int i;
		for ( i = 0; i < 256; ++i) {
			gKeyboardStatus[i] = false;
		}
		gKeyboardStatus[(int)'3'] = true;
		for (i = 0; i < 4; ++i) {
			gCompletedQuarter[i] = false;
		}

		string lFilePath = ExtractConfigData(string(argv[1]) + "config.xml");

		glutInit(&argc,argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

		CreateWindow(lFilePath, gWindowWidth, gWindowHeight);

		glutDisplayFunc(display);
		glutKeyboardFunc(keyPress);
		glutKeyboardUpFunc(keyUp);
		glutIdleFunc(idle);
		glutMouseFunc(mouseClick);
		glutMotionFunc(mouseMotion);
		glutPassiveMotionFunc(mouseMotion);
		glutMainLoop();
		gEnemiesList.clear();
		gShotsList.clear();
		gEnemyShotsList.clear();
		gControllersList.clear();
		return 0;
	}
	catch(exception& e){
		cerr << e.what() << endl;
		return 1;
	}
	catch(string& msg) {
		cerr << msg << endl;
		return 1;
	}
	catch(const char* msg) {
		cerr << msg << endl;
		return 1;
	}
}

// Uses global variables inside de function
string ExtractConfigData(string pConfigFilePath) {
	TiXmlDocument doc(pConfigFilePath);
	if (!doc.LoadFile()) {
		throw string("Erro ao tentar abrir o arquivo.");
	}
	TiXmlElement* lXMLElement = doc.FirstChild()->FirstChild("arquivoDaArena")->ToElement();
	string lDirPath = lXMLElement->Attribute("caminho");
	string lFileName = lXMLElement->Attribute("nome");
	string lFileExtension = lXMLElement->Attribute("tipo");
	lXMLElement = doc.FirstChild()->FirstChild("carro")->ToElement();
	gMovementSpeed = atof( lXMLElement->Attribute("velCarro") );
	gShotSpeed = atof( lXMLElement->Attribute("velTiro") );
	lXMLElement = doc.FirstChild()->FirstChild("carroInimigo")->ToElement();
	gEnemyMovementSpeed = atof( lXMLElement->Attribute("velCarro") );
	gEnemyShotSpeed = atof( lXMLElement->Attribute("velTiro") );
	gEnemyShotFrequency = atof( lXMLElement->Attribute("freqTiro") );
	return lDirPath + lFileName + "." + lFileExtension;
}

void CreateWindow(string pFilePath, GLsizei& pWindowWidth, GLsizei& pWindowHeight) {
	TiXmlDocument doc(pFilePath);
	if (!doc.LoadFile()) {
		throw string("Erro ao tentar abrir o arquivo svg.");
	}
	TiXmlNode* lNode = doc.FirstChild()->FirstChild();

	while (lNode) {
		ExtractNodeData(lNode);
		lNode = lNode->NextSibling();
	}

	setCarControllers();

	gPlayerCar = PaintPlayerCar(gPlayerCar);
	for (list<Car>::iterator it = gEnemiesList.begin(); it != gEnemiesList.end(); it++)
		(*it) = PaintEnemyCar(*it);

	ConvertCoordinates(gOuterCircle);

	pWindowWidth = 500;
	pWindowHeight = 500;

	glutInitWindowSize(pWindowWidth,pWindowHeight);
	glutInitWindowPosition(0,0);
	glutCreateWindow("TC3");
	glClearColor(1.0,1.0,1.0,0.0);
  glShadeModel(	GL_FLAT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 2, 10000);
	// glOrtho( 	  - gOuterCircle.getRadius(), + gOuterCircle.getRadius(),
	// 					  - gOuterCircle.getRadius(),  + gOuterCircle.getRadius(),
	// 					 -1000.0,1000.0);
}

// Uses global variables inside de function
void ExtractNodeData(TiXmlNode* pNode) {
	TiXmlElement* lElement = pNode->ToElement();
	string lID = lElement->Attribute("id");
	if (lID == "Pista")
		ExtractCircuitData(lElement);
	else if (lID == "LargadaChegada")
		gStripeRect = ExtractRectData(lElement);
	else if (lID == "Inimigo")
		gEnemiesList.push_back( ExtractCarData(lElement) );
	else if (lID == "Jogador")
		gPlayerCar = ExtractCarData(lElement);
	else
		throw string("Tag de ID " + lID + " não é reconhecida pelo programa.");
}

// Uses global variables for the inner and outer circles of the circuit
void ExtractCircuitData(TiXmlElement* pElement) {
	Circle auxCircle = ExtractCircleData(pElement);
	if (auxCircle.getRadius() >  gOuterCircle.getRadius()) {
		gInnerCircle = gOuterCircle;
		gOuterCircle = auxCircle;
	}
	else {
		gInnerCircle = auxCircle;
	}
}

Circle ExtractCircleData(TiXmlElement* pElement) {
	GLint lX, lY, lR;
	string lColor;
	Circle lCircle;
	pElement->QueryIntAttribute("cx",&lX);
	pElement->QueryIntAttribute("cy",&lY);
	pElement->QueryIntAttribute("r",&lR);
	lColor = pElement->Attribute("fill");

	lCircle.setXYPosition(lX, lY);
	lCircle.setRadius(lR);
	lCircle.setColor(lColor);
	return lCircle;
}

Car ExtractCarData(TiXmlElement* pElement) {
	GLint lX, lY, lR;
	string lColor;
	Car lCar;
	pElement->QueryIntAttribute("cx",&lX);
	pElement->QueryIntAttribute("cy",&lY);
	pElement->QueryIntAttribute("r",&lR);
	lColor = pElement->Attribute("fill");

	lCar.setXYPosition(lX, lY);
	lCar.setRadius(lR);
	lCar.setColor(lColor);
	return lCar;
}

Rectangle ExtractRectData(TiXmlElement* pElement) {
	GLint lX, lY, lW, lH;
	string lColor;
	Rectangle lRect;
	pElement->QueryIntAttribute("x",&lX);
	pElement->QueryIntAttribute("y",&lY);
	pElement->QueryIntAttribute("width",&lW);
	pElement->QueryIntAttribute("height",&lH);
	lColor = pElement->Attribute("fill");

	lRect.setXYPosition(lX + lW/2, lY + lH/2);
	lRect.setXLength(lW);
	lRect.setYLength(lH);
	lRect.setColor(lColor);
	return lRect;
}

Car PaintPlayerCar(Car pCar) {
	pCar.gun.setColor("darkmoss");
	pCar.body.setColor("moss");
	pCar.hub.setColor("grayblue");
	pCar.wheel.setColor("grayblue");
	pCar.setXYAngle( 90 );
	return pCar;
}

Car PaintEnemyCar(Car pCar) {
	pCar.gun.setColor("black");
	pCar.body.setColor("red");
	pCar.hub.setColor("grayblue");
	pCar.wheel.setColor("grayblue");
	pCar.setXYAngle( 0 );
	pCar.setSteeringAngle(0);
	return pCar;
}

// Uses global variables for the inner and outer circles of the circuit
// Convert all coordinates from the objects from SVG to the virtual world
void ConvertCoordinates(Circle pReferenceCircle) {
	GLfloat lMinSvgX = pReferenceCircle.getX() - pReferenceCircle.getRadius();
	GLfloat lMaxSvgY = pReferenceCircle.getY() + pReferenceCircle.getRadius();
	gOuterCircle.setXYPosition( gOuterCircle.getX() - lMinSvgX, lMaxSvgY - gOuterCircle.getY() );
	gInnerCircle.setXYPosition( gInnerCircle.getX() - lMinSvgX, lMaxSvgY - gInnerCircle.getY() );
	gStripeRect.setXYPosition( gStripeRect.getX() - lMinSvgX, lMaxSvgY - gStripeRect.getY() );
	gPlayerCar.setXYPosition( gPlayerCar.getX() - lMinSvgX, lMaxSvgY - gPlayerCar.getY() );
	for (list<Car>::iterator it = gEnemiesList.begin(); it != gEnemiesList.end(); it++)
		(*it).setXYPosition( (*it).getX() - lMinSvgX, lMaxSvgY - (*it).getY() );
}

// Uses global variables of lists
void setCarControllers() {
	Controller lController;
	for (list<Car>::iterator it = gEnemiesList.begin(); it != gEnemiesList.end(); it++) {
		lController.setCarControlled(&(*it));
		gControllersList.push_back(	lController);
	}
}
