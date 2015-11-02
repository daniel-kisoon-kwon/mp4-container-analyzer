#include <string>
#include "BoxFactory.h"
#include "Box.h"

class BoxFactory
{
public:
	char* unParsedData;	
	
	BoxFactory();
	Box getBox(char* unParsedData);
	~BoxFactory();

private:
	size_t parsedBoxSize;
	char strParsedBoxSize[4];
	char parsedBoxType[5];
	char* parsedBoxPayload;
	bool parsedSubBox;
	
	int convertToInteager(unsigned char* str);
};

BoxFactory::BoxFactory()
{
	memset(strParsedBoxSize, 0, 4);
	memset(parsedBoxType, '\0', 5);
	parsedBoxPayload = (char*)malloc(sizeof(char)*19);
	memset(parsedBoxPayload, '\0', 25);
}

Box BoxFactory::getBox(char* unParsedData)
{
	int i;
	size_t unParsedDataLen = strlen(unParsedData);
	for (i = 0; i < unParsedDataLen; i++)
	{
		if(i>=0 && i<4)
			strParsedBoxSize[i] = unParsedData[i];
		else if(i>=4 && i<8)
			parsedBoxType[i] = unParsedData[i];
		else
		{
			if (strncmp(parsedBoxType, "moov", 4) == 0)
				parsedBoxPayload = "This box has Media data.";
			else
			{
				size_t payloadLen = strlen(unParsedData - 8);
				parsedBoxPayload = (char*)malloc(payloadLen);
			}
		}
	}
}

BoxFactory::~BoxFactory()
{
}

int BoxFactory::convertToInteager(unsigned char* str) {
	int i;
	int ret = 0;
	int byteSize = strlen((char*)str);
	
	for(i = 0; i< byteSize; i++)
		ret = ret | str[byteSize -1 - i]<<i*8;
    return ret;
}