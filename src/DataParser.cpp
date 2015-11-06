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

Box DataParser::getBox(char* unParsedData)
{
	parsedBoxSize = getParsedBoxSize(unParsedData);
	parsedBoxType = getParsedBoxType(unParsedData);

	if (strncmp(parsedBoxType, "moov", 4) ||
		strncmp(parsedBoxType, "trak", 4) ||
		strncmp(parsedBoxType, "mdia", 4) || 
		strncmp(parsedBoxType, "minf", 4) || 
		strncmp(parsedBoxType, "dinf", 4) || 
		strncmp(parsedBoxType, "stbl", 4) || 
		strncmp(parsedBoxType, "udta", 4))
		parsedSubBox = true;

	parsedBoxPayload = getParsedPayload(unParsedData);

	Box box(parsedBoxSize, parsedSubBox, parsedBoxType, parsedBoxPayload);

	return box;
}

size_t DataParser::getParsedBoxSize(char* unParsedData)
{
	if (parsedBoxSize == 0)
	{
		for (int i = 0; i < 4; i++)
			strParsedBoxSize[i] = unParsedData[i];
		parsedBoxSize = (size_t)convertToInteager((unsigned char*)strParsedBoxSize);
	}
	return parsedBoxSize;
}

char* DataParser::getParsedBoxType(char* unParsedData)
{
	int i;

	for (i = 4; i < 8; i++)
		parsedBoxType[i] = unParsedData[i];

	return parsedBoxType;
}


char* DataParser::getParsedPayload(char* unParsedData)
{
	int i, j;
	size_t unParsedDataLen = strlen(unParsedData);

	if (strncmp(parsedBoxType, "moov", 4) == 0)
		parsedBoxPayload = "This box has media data.";
	else
		parsedBoxPayload = (char*)realloc(parsedBoxPayload, strlen(unParsedData - 8));
	for (i = 8, j = 0; i < unParsedDataLen; i++, j++)
		parsedBoxPayload[j] = unParsedData[i];

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
	int byteSize = strlen((char*)str);
	
	for(i = 0; i< byteSize; i++)
		ret = ret | str[byteSize -1 - i]<<i*8;
    return ret;
}