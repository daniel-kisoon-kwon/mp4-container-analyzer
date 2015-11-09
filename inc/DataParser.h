#pragma once

#include "Box.h"
class DataParser
{
public:
	DataParser();
	Box parseBox(char* unParsedData);
	size_t getParsedBoxSize(char* unParsedData);
	char* getParsedBoxType(char* unParsedData);
	char* getParsedPayload(char* unParsedData);
	~DataParser();

private:
	size_t parsedBoxSize;
	char strParsedBoxSize[4];
	char* parsedBoxType;
	char* parsedBoxPayload;
	bool parsedSubBox;

	int convertToInteager(unsigned char* str);
};