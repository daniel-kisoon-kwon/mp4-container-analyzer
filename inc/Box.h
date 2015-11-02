#pragma once

class Box
{
public:
	size_t mSize;
	bool mSubBox;
	char *mType;
	char* mPayload;
	
	Box();
	Box(size_t size, bool SubBox, char *type, char* payload);
	~Box();

private:

};
