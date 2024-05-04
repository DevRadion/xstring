#include "xstring.h"

size_t xStrlen(const char* str) {
	size_t length = 0;
	while (*str++) {
		length++;
	}
	return length;
}

char* xStrcpy(char* dest, const char* src) {
	char* originalDest = dest;
	while (*src) {
		*dest++ = *src++;
	}
	*dest = '\0';
	return originalDest;
}

XString* createString(const char* initial) {
	XString* str = (XString*)pvPortMalloc(sizeof(XString));
	if (str == NULL) {
		return NULL; // Memory allocation failed
	}
	str->length = xStrlen(initial);
	str->data = (char*)pvPortMalloc(str->length + 1); // +1 for null terminator
	if (str->data == NULL) {
		vPortFree(str); // Free the allocated String structure
		return NULL; // Memory allocation failed
	}
	xStrcpy(str->data, initial);
	return str;
}

void destroyString(XString* str) {
	if (str != NULL) {
		if (str->data != NULL) {
			vPortFree(str->data);
		}
		vPortFree(str);
	}
}

void appendString(XString* str, const char* append) {
	uint32_t appendLength = xStrlen(append);
	uint32_t newLength = str->length + appendLength;
	char* newData = (char*)pvPortMalloc(newLength + 1); // +1 for null terminator
	if (newData == NULL) {
		// Memory allocation failed, do nothing
		return;
	}
	xStrcpy(newData, str->data);
	xStrcpy(newData + str->length, append);
	vPortFree(str->data);
	str->data = newData;
	str->length = newLength;
}

void clearString(XString* str) {
	str->length = 0;
	str->data[0] = '\0';
}