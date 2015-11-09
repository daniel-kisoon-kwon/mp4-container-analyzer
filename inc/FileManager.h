#pragma once

#include <stdio.h>

class FileManager
{
public:
	FileManager();
	FileManager(const char* name, const char* type);
	char* getData(long offset, size_t length);
	size_t getFileSize();
	~FileManager();
private:
	FILE *fp;
	char* data;
	
};

