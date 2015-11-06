#include "FileManager.h"
#include <stdlib.h>

FileManager::FileManager()
{
}

FileManager::FileManager(char* name, char* type)
{
	fp = fopen(name, type);

	if (NULL == fp)
		printf("fp is NULL\n");
	data = (char*)malloc(sizeof(char)*4);
}

char* FileManager::getData(long offset, size_t length)
{
	data = (char*)realloc(data, length);
	fseek(fp, offset, SEEK_SET);
	fread(data, sizeof(char), length, fp);

	return data;
}

size_t FileManager::getFileSize()
{
	size_t ret = 0;
	fseek(fp, 0, SEEK_END);
	ret = (size_t)ftell(fp);
	fseek(fp, 0, SEEK_SET);

	return ret;
}

FileManager::~FileManager()
{
	if (NULL != fp)
		fclose(fp);
}