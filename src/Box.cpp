#include <stdlib.h>
#include "Box.h"
Box::Box()
{
}

Box::Box(size_t size, bool subBox, char* type, char* payload)
	: mSize(size), mSubBox(subBox), mType(type), mPayload(payload)
{
}

Box::~Box()
{
}