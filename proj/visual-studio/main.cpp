#include "Box.h"
#include "DataParser.h"
#include "FileManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int main(int argn, char* argv[])
{
	long offset = 0;
	size_t fileSize = 0;
	char* path = argv[2];
	
	
	if(NULL == path)
	{
		printf("Invalid file path!\n");
		return 1;
	}

	FileManager FileReader(path, "rb");
	DataParser Parser;

	fileSize = FileReader.getFileSize();
	while(fileSize != offset)
	{
		//1. Get Box size
		size_t boxSize = Parser.getParsedBoxSize(FileReader.getData(offset, 4));

		//2. Get Box data
		char* boxData = FileReader.getData(offset, boxSize);

		//3. Parse Box data.
		Box box = Parser.parseBox(boxData);
		int payloadLen = box.mSize - 8;

		//4. Print Box data.
		printf("[box] size = %d\n", box.mSize);
		printf("[box] subBox = %d\n", box.mSubBox);
		printf("[box] mType = %s\n", box.mType);
		printf("[box] mPayload = ");
		for (int i = 0; i < payloadLen; i++)
		{
			if (NULL != box.mPayload && 0 != strncmp(box.mType, "mdat", 4))
				printf("%X", box.mPayload[i]);
			else
			{
				printf("%s", box.mPayload);
				break;
			}
		}
		printf("\n\n");

		//5. Reset offset
		if(box.mSubBox == true)
			offset+=8;
		else
			offset += boxSize;
		getch();
	}
	return 0;
}