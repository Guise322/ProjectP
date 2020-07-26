#include "pch.h"
#include <Windows.h>
#include "TextProcessor.h"

extern "C" 
{__declspec (dllexport) char* DllCpp(char* text, int mode)
{
	string res = textProcessor(text, mode);
	char* cstr = new char[res.length() + 1];
	strcpy_s(cstr, res.length() + 1, res.c_str());
	return cstr;
}
}