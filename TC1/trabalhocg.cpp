#include <string.h>
#include <iostream>
using namespace std;
#include <GL/glut.h>
#include "tinyxml.h"
#include "classlib.h"
#include "drawlib.h"
#include "callbacklib.h"

void createWindow(const TiXmlDocument pDoc, GLsizei& pWindowWidth, GLsizei& pWindowHeight);
GLfloat ExtractColorFromNode(const TiXmlNode* pNode, const char* pAttribName);
Square createSquare(const TiXmlDocument pDoc);
Square gSquare;
GLsizei gWindowWidth, gWindowHeight, gLastPointerX, gLastPointerY;
bool gLeftClickInside;

int main(int argc, char** argv)
{
	try {
		if (argc != 2) {
			throw runtime_error("Número de argumentos inválido. É necessário informar o diretório do arquivo config.xml, e apenas este argumento.");
		}

		string filePath = string(argv[1]) + "config.xml";
		TiXmlDocument doc(filePath);
		if (!doc.LoadFile()) {
			throw runtime_error("Erro ao tentar abrir o arquivo.");
		}

		glutInit(&argc,argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		createWindow(doc, gWindowWidth, gWindowHeight);
		gSquare = createSquare(doc);
		gSquare.setVisible(false);
		gLeftClickInside = false;
		glutDisplayFunc(display);
		glutMouseFunc(mouseClick);
		glutMotionFunc(mouseMotion);
		glutMainLoop();

		return 0;
	}
	catch(exception& e){
		cerr << e.what() << endl;
		return 1;
	} 	
	catch(const char* msg) {
		cerr << msg << endl;
		return 1;
	}	
}

void createWindow(const TiXmlDocument pDoc, GLsizei& pWindowWidth, GLsizei& pWindowHeight) {
	// Create Window and assign the size to the input parameters pWindowWidth and pWindowHeight
	const TiXmlNode* lWindowNode = pDoc.FirstChild()->FirstChild("janela");
	pWindowWidth = (GLsizei) atoi(lWindowNode->FirstChild("largura")->FirstChild()->ToText()->Value());
	pWindowHeight = (GLsizei) atoi(lWindowNode->FirstChild("altura")->FirstChild()->ToText()->Value());
	GLfloat R = ExtractColorFromNode(lWindowNode->FirstChild("fundo"), "corR");
	GLfloat G = ExtractColorFromNode(lWindowNode->FirstChild("fundo"), "corG");
	GLfloat B = ExtractColorFromNode(lWindowNode->FirstChild("fundo"), "corB");
	string title = lWindowNode->FirstChild("titulo")->FirstChild()->ToText()->Value();
	
	glutInitWindowSize(pWindowWidth,pWindowHeight);
	glutInitWindowPosition(100,100);
	glutCreateWindow(title.c_str());
	glClearColor(R,G,B,0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
}

GLfloat ExtractColorFromNode(const TiXmlNode* pNode, const char* pAttribName) {
	const TiXmlElement* lElement = pNode->ToElement();
	double lValue;
	if (lElement->QueryDoubleAttribute(pAttribName, &lValue)==TIXML_SUCCESS)
		return (GLfloat) lValue;
	else 
		throw runtime_error("Erro ao ler o atributo " + string(pAttribName) + ".");
}

Square createSquare(const TiXmlDocument pDoc) {
	Square outSquare;
	const TiXmlNode* lSquareNode = pDoc.FirstChild()->FirstChild("quadrado");
	GLfloat R = ExtractColorFromNode(lSquareNode, "corR");
	GLfloat G = ExtractColorFromNode(lSquareNode, "corG");
	GLfloat B = ExtractColorFromNode(lSquareNode, "corB");
	int lSize;
	if ( !(lSquareNode->ToElement()->QueryIntAttribute("tamanho",&lSize) == TIXML_SUCCESS) )
		throw runtime_error("Erro ao ler o atributo tamanho.");
	outSquare.setSize( lSize );
	outSquare.setRGB(R, G, B);
	return outSquare;
}

