#include "Box.h"
#include "DataParser.h"
#include "FileManager.h"
#include <stdio.h>

int main(int argn, char* argv[])
{
	long offset = 0;
	size_t fileSize = 0;
	size_t boxSize = 0;
	char* boxData = NULL;
	Box box;
	FileManager FileReader("E:\\devel\\c++\\mp4-container-analyzer\\res\\test.mp4", "rb");
	DataParser Parser;

	fileSize = FileReader.getFileSize();
	boxSize = Parser.getParsedBoxSize(FileReader.getData(offset, 4));
	boxData = FileReader.getData(offset, boxSize);
	box = Parser.getBox(boxData);
	return 0;
}