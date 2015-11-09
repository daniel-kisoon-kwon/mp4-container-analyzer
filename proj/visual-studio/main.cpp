#include "Box.h"
#include "DataParser.h"
#include "FileManager.h"
#include <stdio.h>

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

		//4. Refresh offset
		if(box.mSubBox == true)
			offset+=8;
		else
			offset += boxSize;
	}
	return 0;
}