// tutorial demo program
#include <stdio.h>
#include <string.h>
#include "tinyxml.h"

#include <iostream>
using namespace std;

// ----------------------------------------------------------------------
// STDOUT dump and indenting utility functions
// ----------------------------------------------------------------------
const unsigned int NUM_INDENTS_PER_SPACE=2;

const char * getIndent( unsigned int numIndents )
{
	static const char * pINDENT="                                      + ";
	static const unsigned int LENGTH=strlen( pINDENT );
	unsigned int n=numIndents*NUM_INDENTS_PER_SPACE;
	if ( n > LENGTH ) n = LENGTH;

	return &pINDENT[ LENGTH-n ];
}

// same as getIndent but no "+" at the end
const char * getIndentAlt( unsigned int numIndents )
{
	static const char * pINDENT="                                        ";
	static const unsigned int LENGTH=strlen( pINDENT );
	unsigned int n=numIndents*NUM_INDENTS_PER_SPACE;
	if ( n > LENGTH ) n = LENGTH;

	return &pINDENT[ LENGTH-n ];
}

int dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent)
{
	if ( !pElement ) return 0;

	TiXmlAttribute* pAttrib=pElement->FirstAttribute();
	int i=0;
	int ival;
	double dval;
	const char* pIndent=getIndent(indent);
	printf("\n");
	while (pAttrib)
	{
		printf( "%s%s: value=[%s]", pIndent, pAttrib->Name(), pAttrib->Value());

		if (pAttrib->QueryIntValue(&ival)==TIXML_SUCCESS)    printf( " int=%d", ival);
		if (pAttrib->QueryDoubleValue(&dval)==TIXML_SUCCESS) printf( " d=%1.1f", dval);
		printf( "\n" );
		i++;
		pAttrib=pAttrib->Next();
	}
	return i;	
}

void dump_to_stdout( TiXmlNode* pParent, unsigned int indent = 0 )
{
	if ( !pParent ) return;

	TiXmlNode* pChild;
	TiXmlText* pText;
	int t = pParent->Type();
	printf( "%s", getIndent(indent));
	int num;

	switch ( t )
	{
	case TiXmlNode::TINYXML_DOCUMENT:
		printf( "Document" );
		break;

	case TiXmlNode::TINYXML_ELEMENT:
		printf( "Element [%s]", pParent->Value() );
		num=dump_attribs_to_stdout(pParent->ToElement(), indent+1);
		switch(num)
		{
			case 0:  printf( " (No attributes)"); break;
			case 1:  printf( "%s1 attribute", getIndentAlt(indent)); break;
			default: printf( "%s%d attributes", getIndentAlt(indent), num); break;
		}
		break;

	case TiXmlNode::TINYXML_COMMENT:
		printf( "Comment: [%s]", pParent->Value());
		break;

	case TiXmlNode::TINYXML_UNKNOWN:
		printf( "Unknown" );
		break;

	case TiXmlNode::TINYXML_TEXT:
		pText = pParent->ToText();
		printf( "Text: [%s]", pText->Value() );
		break;

	case TiXmlNode::TINYXML_DECLARATION:
		printf( "Declaration" );
		break;
	default:
		break;
	}
	printf( "\n" );
	for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
		dump_to_stdout( pChild, indent+1 );
	}
}

unsigned char ExtractColorFromNode(TiXmlNode* pNode, const char* pAttribName) {
	TiXmlElement* lElement = pNode->ToElement();
	int lValor;
	if (lElement->QueryIntAttribute(pAttribName, &lValor)==TIXML_SUCCESS)
		return (unsigned char) lValor;
	else 
		throw runtime_error("Erro ao ler o atributo " + string(pAttribName) + ".");
}

typedef struct {
	struct Janela {
		string titulo;
		int largura, altura;
		struct Fundo {
			unsigned char corR, corG, corB;
		} fundo;	
	} janela;
	struct Quadrado {
		int tamanho;
		unsigned char corR, corG, corB;
	} quadrado;
} Aplicacao;

Aplicacao ExtractAppConfig(string fileDir) {
	Aplicacao app;
	string filePath = fileDir + "config.xml";
	TiXmlDocument doc(filePath);
	if (!doc.LoadFile()) {
		throw runtime_error("Erro ao tentar abrir o arquivo.");
	}
	TiXmlNode* lNodeAplicacao = doc.FirstChild();
	TiXmlNode* lNodeJanela = lNodeAplicacao->FirstChild("janela");
	TiXmlNode* lNodeQuadrado = lNodeAplicacao->FirstChild("quadrado");
	app.janela.largura = atoi(lNodeJanela->FirstChild("largura")->FirstChild()->ToText()->Value());
	app.janela.altura = atoi(lNodeJanela->FirstChild("altura")->FirstChild()->ToText()->Value());
	app.janela.fundo.corR = ExtractColorFromNode(lNodeJanela->FirstChild("fundo"), "corR");
	app.janela.fundo.corG = ExtractColorFromNode(lNodeJanela->FirstChild("fundo"), "corG");
	app.janela.fundo.corB = ExtractColorFromNode(lNodeJanela->FirstChild("fundo"), "corB");
	app.janela.titulo = lNodeJanela->FirstChild("titulo")->FirstChild()->ToText()->Value();
	int lValor;
	if (lNodeQuadrado->ToElement()->QueryIntAttribute("tamanho",&lValor) == TIXML_SUCCESS )
		app.quadrado.tamanho = lValor;
	app.quadrado.corR = ExtractColorFromNode(lNodeQuadrado, "corR");
	app.quadrado.corG = ExtractColorFromNode(lNodeQuadrado, "corG");
	app.quadrado.corB = ExtractColorFromNode(lNodeQuadrado, "corB");
	return app;
}

int main(int argc, char const *argv[])
{
	try {
		if (argc != 2) {
			throw runtime_error("Número de argumentos inválido. É necessário informar o diretório do arquivo config.xml, e apenas este argumento.");
		}
		Aplicacao app = ExtractAppConfig(argv[1]);
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