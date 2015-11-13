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
	int depth = 0;
	long endOfDepth[128] = {0,};

	if(NULL == path)
	{
		printf("Invalid file path!\n");
		return 1;
	}

	FileManager FileReader(path, "rb");
	FileManager FileWriter("output", "wa");
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
		printf("[%s] size(%2d), hasSubBox(%d)\n", box.mType, box.mSize, box.mSubBox);
		
		//5. Reset offset
		if(box.mSubBox == true)
		{
			endOfDepth[depth] = offset + boxSize;
			depth++;
			offset+=8;
		}
		else
			offset += boxSize;

		for (int i = depth; i >=0; i--)
			if(endOfDepth[depth-1] == offset)
				depth--;
		if( depth > 0)
		{
			for (int i = 0; i < depth; i++)
				printf("   ");
		}
		//getch();
	}
	return 0;
}