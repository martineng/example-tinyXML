// xmlTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include "iostream"
#include "tinyxml2/tinyxml2.h"

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS){ printf("Error: %i\n, a_eResult"); return a_eResult; }
#endif

using namespace std;
using namespace tinyxml2;
int secondMain();
int readXML();
int readFromXML();

int main()
{
	int select;

	//secondMain();
	readFromXML();

	cin >> select;
	cout << select;
}

// Demo on Write into XML
int secondMain()
{

	XMLDocument xmlDoc;
	XMLNode * pRoot = xmlDoc.NewElement("Root");

	xmlDoc.InsertFirstChild(pRoot);
	XMLElement * pElement = xmlDoc.NewElement("IntValue");

	pElement->SetText(44444);
	pRoot->InsertFirstChild(pElement);

	pElement = xmlDoc.NewElement("FloatValue");
	pElement->SetText(0.5f);
	pRoot->InsertEndChild(pElement);

	pElement = xmlDoc.NewElement("Date");
	pElement->SetAttribute("day", 26);
	pElement->SetAttribute("month", "April");
	pElement->SetAttribute("year", 2014);
	pElement->SetAttribute("dateFormat", "26/04/2014");
	pRoot->InsertEndChild(pElement);

	XMLError eResult = xmlDoc.SaveFile("TestData.xml");
	XMLCheckResult(eResult);
}

// Associate secondMain(), demo on read from different data type
int readXML()
{
	XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile("TestData.xml");
	XMLCheckResult(eResult);

	// Extracting data from an XMLDocument
	XMLNode * pRoot = xmlDoc.FirstChild();

	if (pRoot == nullptr)
	{
		return XML_ERROR_FILE_READ_ERROR;
	}// END if

	/* Loading int */
	XMLElement * pElement = pRoot->FirstChildElement("IntValue");
	
	if (pElement == nullptr)
	{
		return XML_ERROR_PARSING_ELEMENT;
	}

	int iOutInt;
	eResult = pElement->QueryIntText(&iOutInt);
	XMLCheckResult(eResult);

	/* Loading float*/
	pElement = pRoot->FirstChildElement("FloatValue");
	
	if (pElement == nullptr)
	{
		return XML_ERROR_PARSING_ELEMENT;
	}

	float fOutFloat;

	eResult = pElement->QueryFloatText(&fOutFloat);
	XMLCheckResult(eResult);

	/* Dealing with Multiple*/
	pElement = pRoot->FirstChildElement("Date");

	if (pElement == nullptr)
	{
		return XML_ERROR_PARSING_ELEMENT;
	} // ENG if

	int iOutDay, iOutYear;

	eResult = pElement->QueryIntAttribute("day", &iOutDay);
	XMLCheckResult(eResult);

	eResult = pElement->QueryIntAttribute("year", &iOutYear);
	XMLCheckResult(eResult);

	cout << iOutInt << endl;
	cout << fOutFloat << endl;
	cout << iOutDay << ", " << iOutYear << endl;

	return XML_SUCCESS;
}

int readFromXML()
{
	/* To Access child of child element, http://www.dinomage.com/2012/01/tutorial-using-tinyxml-part-1/  */
	XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile("object.xml");
	XMLCheckResult(eResult);

	const char * oEnemyName = nullptr;
	int oEnemyAttack, oEnemyHealth;

	
	XMLNode * pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr)
	{
		return XML_ERROR_FILE_READ_ERROR;
	}

	XMLElement * pElement = pRoot->FirstChildElement("Enemy1");
	if (pElement == nullptr)
	{
		return XML_ERROR_PARSING_ELEMENT;
	}

	/* To read String */
	oEnemyName = pElement->Attribute("name");

	if (oEnemyName == nullptr)
	{
		return XML_ERROR_PARSING_ATTRIBUTE;
	}
	
	string strOutFormat = oEnemyName;
	
	eResult = pElement->QueryIntAttribute("attack", &oEnemyAttack);
	XMLCheckResult(eResult);

	eResult = pElement->QueryIntAttribute("health", &oEnemyHealth);
	XMLCheckResult(eResult);

	cout << "Name: " << oEnemyName << "\nAttack: " << oEnemyAttack << "\nHealth: " << oEnemyHealth << endl;

	return XML_SUCCESS;
}
