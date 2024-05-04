#ifndef __XSTRING
#define __XSTRING

#include "FreeRTOS.h"

typedef struct {
	char* data;
	uint32_t length;
} XString;

size_t xStrlen(const char* str);
char* xStrcpy(char* dest, const char* src);
XString* createString(const char* initial);
void destroyString(XString* str);
void appendString(XString* str, const char* append);
void clearString(XString* str);


#endif // !__XSTRING
