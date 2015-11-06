#include "Box.h"
#include <stdio.h>

Box::Box()
{
}

Box::Box(size_t size, bool subBox, char* type, char* payload)
	: mSize(size), mSubBox(subBox), mType(type), mPayload(payload)
{
	printf("[box] size = %d\n", mSize);
	printf("[box] subBox = %d\n", mSubBox);
	printf("[box] mType = %s\n", mType);
	printf("[box] mPayload = %s\n", mPayload);
}

Box::~Box()
{
}