#include <string.h>
#include <iostream>
using namespace std;
#include <fstream>
#include <GL/glut.h>
#include "tinyxml.h"

string ExtractFilePath(string pConfigFilePath);

int main(int argc, char** argv)
{
	try {
		if (argc != 2) {
			throw runtime_error("Número de argumentos inválido. É necessário informar o diretório do arquivo config.xml, e apenas este argumento.");
		}
		
		string lFilePath = ExtractFilePath(string(argv[1]) + "config.xml");
		ifstream inputFile;
		inputFile.open(lFilePath.c_str());
		// string input;
		// inputFile >> input;
		// cout << input << endl;
		inputFile.close();
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

string ExtractFilePath(string pConfigFilePath) {
	TiXmlDocument doc(pConfigFilePath);
	if (!doc.LoadFile()) {
		throw runtime_error("Erro ao tentar abrir o arquivo.");
	}
	TiXmlElement* lXMLElement = doc.FirstChild()->FirstChild("arquivoDaArena")->ToElement();
	string lDirPath = lXMLElement->Attribute("caminho");
	string lFileName = lXMLElement->Attribute("nome");
	string lFileExtension = lXMLElement->Attribute("tipo");
	return lDirPath + lFileName + "." + lFileExtension;
}