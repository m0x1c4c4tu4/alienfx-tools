#pragma once
#include <wtypes.h>
#include <string>

DWORD GetRegData(HKEY key, int vindex, char* name, byte** data);
std::string GetRegString(byte* data, int len);