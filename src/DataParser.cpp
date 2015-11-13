#include "DataParser.h"
#include <stdlib.h>
#include <string>

DataParser::DataParser()
{
	parsedBoxSize = 0;
	memset(strParsedBoxSize, 0, 4);
	parsedBoxType = (char*)malloc(sizeof(char) * 5);
	memset(parsedBoxType, '\0', 5);
	parsedBoxPayload = (char*)malloc(sizeof(char)*25);
	memset(parsedBoxPayload, '\0', 25);
	parsedSubBox = false;
}

Box DataParser::parseBox(char* unParsedData)
{
	parsedBoxSize = getParsedBoxSize(unParsedData);
	parsedBoxType = getParsedBoxType(unParsedData);

	if (0 == strncmp(parsedBoxType, "moov", 4) ||
		0 == strncmp(parsedBoxType, "trak", 4) ||
		0 == strncmp(parsedBoxType, "mdia", 4) || 
		0 == strncmp(parsedBoxType, "minf", 4) || 
		0 == strncmp(parsedBoxType, "dinf", 4) || 
		0 == strncmp(parsedBoxType, "stbl", 4) || 
		0 == strncmp(parsedBoxType, "udta", 4))
		parsedSubBox = true;
	else
		parsedSubBox = false;

	parsedBoxPayload = getParsedPayload(unParsedData);

	Box box(parsedBoxSize, parsedSubBox, parsedBoxType, parsedBoxPayload);

	return box;
}

size_t DataParser::getParsedBoxSize(char* unParsedData)
{
	for (int i = 0; i < 4; i++)
		strParsedBoxSize[i] = unParsedData[i];
	parsedBoxSize = (size_t)convertToInteager((unsigned char*)strParsedBoxSize);
	
	return parsedBoxSize;
}

char* DataParser::getParsedBoxType(char* unParsedData)
{
	int i,j = 0;

	for (i = 4; i < 8; i++)
		parsedBoxType[j++] = unParsedData[i];

	return parsedBoxType;
}


char* DataParser::getParsedPayload(char* unParsedData)
{
	int i = 8;
	int j = 0;
	int payloadLen = parsedBoxSize - 8;

	if (strncmp(parsedBoxType, "mdat", 4) == 0)
	{
		parsedBoxPayload = (char*)realloc(parsedBoxPayload, 25);
		memset(parsedBoxPayload, 0, 25);
		memcpy(parsedBoxPayload, "This box has media data.", 25);
	}
	else
	{
		parsedBoxPayload = (char*)realloc(parsedBoxPayload, payloadLen);
		for (i; i < payloadLen; i++)
			parsedBoxPayload[j++] = unParsedData[i];
	}
	
	return parsedBoxPayload;
}

DataParser::~DataParser()
{
	free(parsedBoxType);
	free(parsedBoxPayload);
}




int DataParser::convertToInteager(unsigned char* str) {
	int i;
	int ret = 0;
	int byteSize = sizeof(str);
	
	for(i = 0; i< byteSize; i++)
		ret = ret | str[byteSize -1 - i]<<i*8;
    return ret;
}