#ifndef COMMON_STRING_H
#define COMMON_STRING_H

#include <vector>
#include <string>
#include <windows.h>

using namespace std;

namespace Common{

string WS2S(const wstring& ws);

wstring S2WS(const string& s);

wstring StringToWstring(const string& src, int charset = CP_ACP);

string WstringToString(const wstring& src, int charset = CP_ACP);

string ConvertString(const string& src, int old_charset, int new_charset);

}

#endif