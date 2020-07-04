#include "pch.h"

#include "TextProcessor.h"

extern "C" 
{__declspec (dllexport) char* dllCpp(int mode)
{
	string res = textProcessor(mode);
	char* cstr = new char[res.length() + 1];
	strcpy_s(cstr, res.length() + 1, res.c_str());
	return cstr;
}
}