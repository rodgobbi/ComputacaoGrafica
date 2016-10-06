#include <string.h>
#include <iostream>
using namespace std;
#include <GL/glut.h>
#include "tinyxml.h"
#include "classlib.h"
#include "drawlib.h"
#include "callbacklib.h"

string ExtractFilePath(string pConfigFilePath);
void CreateWindow(string pFilePath, GLsizei& pWindowWidth, GLsizei& pWindowHeight);
Circle ExtractCircleData(TiXmlElement* pElement);
Car ExtractCarData(TiXmlElement* pElement);
Rectangle ExtractRectData(TiXmlElement* pElement);

GLsizei gWindowWidth, gWindowHeight;
Circle gOuterCircle, gInnerCircle, gEnemyCircle1, gEnemyCircle2, gEnemyCircle3;
Car gPlayerCar;
Rectangle gStripeRect;
bool gKeyboardStatus[256];
GLfloat gMovementSpeed = 0.1, gRotationSpeed = 0.001;

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

		string lFilePath = ExtractFilePath(string(argv[1]) + "config.xml");

		glutInit(&argc,argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

		CreateWindow(lFilePath, gWindowWidth, gWindowHeight);

		glutDisplayFunc(display);
		glutKeyboardFunc(keyPress);
		glutKeyboardUpFunc(keyUp);
		glutIdleFunc(idle);
		glutMainLoop();

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

string ExtractFilePath(string pConfigFilePath) {
	TiXmlDocument doc(pConfigFilePath);
	if (!doc.LoadFile()) {
		throw string("Erro ao tentar abrir o arquivo.");
	}
	TiXmlElement* lXMLElement = doc.FirstChild()->FirstChild("arquivoDaArena")->ToElement();
	string lDirPath = lXMLElement->Attribute("caminho");
	string lFileName = lXMLElement->Attribute("nome");
	string lFileExtension = lXMLElement->Attribute("tipo");
	return lDirPath + lFileName + "." + lFileExtension;
}

void CreateWindow(string pFilePath, GLsizei& pWindowWidth, GLsizei& pWindowHeight) {
	TiXmlDocument doc(pFilePath);
	if (!doc.LoadFile()) {
		throw string("Erro ao tentar abrir o arquivo svg.");
	}
	TiXmlNode* lNode = doc.FirstChild()->FirstChild();

	gOuterCircle = ExtractCircleData(lNode->ToElement());

	pWindowWidth = (GLsizei) gOuterCircle.getRadius() * 2;
	pWindowHeight = (GLsizei) gOuterCircle.getRadius() * 2;

	glutInitWindowSize(pWindowWidth,pWindowHeight);
	glutInitWindowPosition(50,50);
	glutCreateWindow("TC2");
	glClearColor(1.0,1.0,1.0,0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( 	gOuterCircle.getX() - gOuterCircle.getRadius(),gOuterCircle.getX() + gOuterCircle.getRadius(),
						 gOuterCircle.getY() - gOuterCircle.getRadius(), gOuterCircle.getY() + gOuterCircle.getRadius(),
						 -1.0,1.0);

	lNode = lNode->NextSibling();
	gInnerCircle = ExtractCircleData(lNode->ToElement());

	lNode = lNode->NextSibling();
	gStripeRect = ExtractRectData(lNode->ToElement());

	lNode = lNode->NextSibling();
	gEnemyCircle1 = ExtractCircleData(lNode->ToElement());

	lNode = lNode->NextSibling();
	gEnemyCircle2 = ExtractCircleData(lNode->ToElement());

	lNode = lNode->NextSibling();
	gEnemyCircle3 = ExtractCircleData(lNode->ToElement());

	lNode = lNode->NextSibling();
	gPlayerCar = ExtractCarData(lNode->ToElement());
}

// Uses global variables inside de function
// void ExtractNodeData(TiXmlNode* pNode) {
// 	TiXmlElement* lElement = pNode->ToElement();
// 	string lID = lElement->Attribute("id");
// 	if ()
//
// 	else if ("LargadaChegada")
// 		gStripeRect = ExtractRectData(lElement);
// }

Circle ExtractCircleData(TiXmlElement* pElement) {
	GLint lX, lY, lR;
	string lColor;
	Circle lCircle;
	pElement->QueryIntAttribute("cx",&lX);
	pElement->QueryIntAttribute("cy",&lY);
	pElement->QueryIntAttribute("r",&lR);
	lColor = pElement->Attribute("fill");

	lCircle.setPosition(lX, lY);
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

	lCar.setPosition(lX, lY);
	lCar.setRadius(lR);
	lCar.setColor(lColor);
	lCar.setDirection( M_PI/2 );
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

	lRect.setPosition(lX + lW/2, lY + lH/2);
	lRect.setWidth(lW);
	lRect.setHeight(lH);
	lRect.setColor(lColor);
	return lRect;
}
