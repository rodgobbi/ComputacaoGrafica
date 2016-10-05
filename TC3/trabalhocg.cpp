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
	GLint lX, lY, lW, lH, lR;
	string lColor;
	TiXmlDocument doc(pFilePath);
	if (!doc.LoadFile()) {
		throw string("Erro ao tentar abrir o arquivo svg.");
	}
	TiXmlNode* lNode = doc.FirstChild()->FirstChild();
	lNode->ToElement()->QueryIntAttribute("cx",&lX);
	lNode->ToElement()->QueryIntAttribute("cy",&lY);
	lNode->ToElement()->QueryIntAttribute("r",&lR);
	lColor = lNode->ToElement()->Attribute("fill");

	gOuterCircle.setPosition(lX, lY);
	gOuterCircle.setRadius(lR);
	gOuterCircle.setColor(lColor);

	pWindowWidth = (GLsizei) lR * 2;
	pWindowHeight = (GLsizei) lR * 2;
	
	glutInitWindowSize(pWindowWidth,pWindowHeight);
	glutInitWindowPosition(50,50);
	glutCreateWindow("TC2");
	glClearColor(1.0,1.0,1.0,0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( (GLfloat) (lX - lR),(GLfloat) (lX + lR),
						 (GLfloat) (lY - lR),(GLfloat) (lY + lR),-1.0,1.0);

	lNode = lNode->NextSibling();
	lNode->ToElement()->QueryIntAttribute("cx",&lX);
	lNode->ToElement()->QueryIntAttribute("cy",&lY);
	lNode->ToElement()->QueryIntAttribute("r",&lR);
	lColor = lNode->ToElement()->Attribute("fill");

	gInnerCircle.setPosition(lX, lY);
	gInnerCircle.setRadius(lR);
	gInnerCircle.setColor(lColor);

	lNode = lNode->NextSibling();
	lNode->ToElement()->QueryIntAttribute("x",&lX);
	lNode->ToElement()->QueryIntAttribute("y",&lY);
	lNode->ToElement()->QueryIntAttribute("width",&lW);
	lNode->ToElement()->QueryIntAttribute("height",&lH);
	lColor = lNode->ToElement()->Attribute("fill");

	gStripeRect.setPosition(lX + lW/2, lY + lH/2);
	gStripeRect.setWidth(lW);
	gStripeRect.setHeight(lH);
	gStripeRect.setColor(lColor);

	lNode = lNode->NextSibling();
	lNode->ToElement()->QueryIntAttribute("cx",&lX);
	lNode->ToElement()->QueryIntAttribute("cy",&lY);
	lNode->ToElement()->QueryIntAttribute("r",&lR);
	lColor = lNode->ToElement()->Attribute("fill");

	gEnemyCircle1.setPosition(lX, lY);
	gEnemyCircle1.setRadius(lR);
	gEnemyCircle1.setColor(lColor);

	lNode = lNode->NextSibling();
	lNode->ToElement()->QueryIntAttribute("cx",&lX);
	lNode->ToElement()->QueryIntAttribute("cy",&lY);
	lNode->ToElement()->QueryIntAttribute("r",&lR);
	lColor = lNode->ToElement()->Attribute("fill");

	gEnemyCircle2.setPosition(lX, lY);
	gEnemyCircle2.setRadius(lR);
	gEnemyCircle2.setColor(lColor);

	lNode = lNode->NextSibling();
	lNode->ToElement()->QueryIntAttribute("cx",&lX);
	lNode->ToElement()->QueryIntAttribute("cy",&lY);
	lNode->ToElement()->QueryIntAttribute("r",&lR);
	lColor = lNode->ToElement()->Attribute("fill");

	gEnemyCircle3.setPosition(lX, lY);
	gEnemyCircle3.setRadius(lR);
	gEnemyCircle3.setColor(lColor);

	lNode = lNode->NextSibling();
	lNode->ToElement()->QueryIntAttribute("cx",&lX);
	lNode->ToElement()->QueryIntAttribute("cy",&lY);
	lNode->ToElement()->QueryIntAttribute("r",&lR);
	lColor = lNode->ToElement()->Attribute("fill");

	gPlayerCar.setPosition(lX, lY);
	gPlayerCar.setRadius(lR);
	gPlayerCar.setColor(lColor);
	gPlayerCar.setDirection( M_PI/2 );
}