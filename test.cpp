#include "stdafx.h"
#include "path.hpp"
#include "string.hpp"
using namespace common;

void test_path_hpp()
{
	string d = "c:\\path\\to\\file.ext";
	wstring d2 = L"c:\\path\\to\\file.ext";

	string a1 = GetPathFolderName<char>(d.c_str());
	string a2 = GetPathDirectory<char>(d.c_str());
	string a3 = GetPathFilename<char>(d.c_str());
	string a4 = GetPathExtension<char>(d.c_str());
	string a5 = GetPathFullname<char>(d.c_str());
	string a6 = GetPathDrive<char>(d.c_str());

	wstring b1 = GetPathFolderName<wchar_t>(d2.c_str());
	wstring b2 = GetPathDirectory<wchar_t>(d2.c_str());
	wstring b3 = GetPathFilename<wchar_t>(d2.c_str());
	wstring b4 = GetPathExtension<wchar_t>(d2.c_str());
	wstring b5 = GetPathFullname<wchar_t>(d2.c_str());
	wstring b6 = GetPathDrive<wchar_t>(d2.c_str());

	string exe = GetExeDir<char>(0);
	string exe1 = GetExeDir<char>(1);
	wstring exe2 = GetExeDir<wchar_t>(0);
	wstring exe3 = GetExeDir<wchar_t>(1);

	string cwd = GetCurrentDir<char>();
	wstring cwd1 = GetCurrentDir<wchar_t>();
}

void test_string_hpp()
{
	string a = ReplaceAll<char>(string("abbabb"), "ab", "a"); //abbabb => aa
	wstring aa = ReplaceAll<wchar_t>(wstring(L"abbabb"), L"ab", L"a");
	string b = ReplaceAllDistinct<char>(string("abbabb"), "ab", "a" ); //abbabb => abab
	wstring bb = ReplaceAllDistinct<wchar_t>(wstring(L"abbabb"), L"ab", L"a");

	string trim = " aa bb cc ";
	Strip<char>(trim);
	wstring wtrim = L" aa bb cc \r\n\t";
	Strip<wchar_t>(wtrim, L" \r\n\t");
	wstring gtrim = L" aa bb cc ";
	wstring gtrim1 = GetStrip<wchar_t>(gtrim);

	string qt1 = "\"abc\"";
	string qt2 = "[abc]";
	wstring qt3 = L" abc  ";
	wstring qt4 = L"{abc";
	bool has1 = HasQuote<char>(qt1);
	bool has2 = HasQuote<char>(qt2, '[');
	bool has3 = HasQuote<wchar_t>(qt3, ' ');
	bool has4 = HasQuote<wchar_t>(qt4, '{');
	Unquote<char>(qt1);
	Unquote<char>(qt2, ']');
	Unquote<wchar_t>(qt3, ' ');
	Unquote<wchar_t>(qt4, '{');
	string qt11 = GetQuote<char>(qt1);
	string qt21 = GetQuote<char>(qt2, '[');
	wstring qt31 = GetQuote<wchar_t>(qt3, ' ');
	wstring qt41 = GetQuote<wchar_t>(qt4, '{');

	vector<string> v1 = Split<char>("abc", ";");
	vector<wstring> v2 = Split<wchar_t>(L"abc;", L";");
	vector<string> v3 = Split<char>("abc  efg  hij ", "  ");
	vector<wstring> v4 = Split<wchar_t>(L";abc;efg;hij", L";");

	string j1 = Joint<char>(v1, "_");
	wstring j2 = Joint<wchar_t>(v2, L"|");
	string j3 = Joint<char>(v3, "**");
	wstring j4 = Joint<wchar_t>(v4, L"#");

	string fmt = FormatString<char>(1024, "%s%d%c%f%x", "abc", 1, 'X', 0.1, 0x1234);
	wstring fmt1 = FormatString<wchar_t>(1024, L"%s%d%c%f%x", L"abc", 1, 'X', 0.1, 0x1234);
	string fmt3 = format_string("%s%d%c%f%x", "abc", 1, 'X', 0.1, 0x1234);

	string append = "1 + 2 = ";
	string& append_ref = FormatAppend<char>(append, 20, "%d", 3);
	string append1 = FormatAppend<char>(append, 20, "%d", 3);
	wstring append2 = L"abc + def = ";
	wstring& append2_ref = FormatAppend<wchar_t>(append2, L"%s%s", L"abc", L"def");
	wstring append3 = FormatAppend<wchar_t>(append2, L"%s%s", L"abc", L"def");

	OutputDebugMessage<char>("%s%d%c%f%x", "abc", 1, 'X', 0.1, 0x1234);
	OutputDebugMessage<char>(100, "%s%d%c%f%x", "abc", 1, 'X', 0.1, 0x1234);
	OutputDebugMessage<wchar_t>(L"%s%d%c%f%x", L"abc", 1, 'X', 0.1, 0x1234);
	OutputDebugMessage<wchar_t>(100, L"%s%d%c%f%x", L"abc", 1, 'X', 0.1, 0x1234);

	string str = "abcdefg";
	string sub = "EfG";
	int pos = stristr(str, sub);
	wstring wstr = L"ABCED";
	int pos1 = StrIStr<wstring>(wstr, L"abce");
}
