#include "stdafx.h"
#include "string.h"
#include <stdio.h>
#include <wchar.h>
#include <stdarg.h>
#include <wtypes.h>
#include <stdlib.h>
#include <locale.h>
#include <direct.h>

namespace common{

	string WS2S(const wstring& ws)
	{
		string loc = setlocale(LC_ALL, "chs");        // curLocale = "C";
		//setlocale(LC_ALL, "chs");
		const wchar_t* src = ws.c_str();
		size_t dsize = 2*ws.size() + 1;
		char *dest = new char[dsize];
		memset(dest, 0, dsize);
		size_t ret;
		wcstombs_s(&ret, dest, dsize, src, dsize);
		string result = dest;
		delete []dest;
		setlocale(LC_ALL, loc.c_str());
		return result;
	}

	wstring S2WS(const string& s)
	{
		setlocale(LC_ALL, "chs"); 
		const char* src = s.c_str();
		size_t dsize = s.size() + 1;
		wchar_t *dest = new wchar_t[dsize];
		wmemset(dest, 0, dsize);
		size_t ret;
		mbstowcs_s(&ret, dest, dsize, src, dsize);
		wstring result = dest;
		delete []dest;
		setlocale(LC_ALL, "C");
		return result;
	}

	wchar_t* _char_to_wchar(const char* src, int src_len, int charset, int& des_len)
	{
		if (src == NULL || 0 == src_len)
		{
			return NULL;
		}

		des_len = MultiByteToWideChar(charset, 0, src, src_len, NULL, NULL );

		if (des_len == 0)
			return NULL;

		wchar_t* des = new wchar_t[des_len + 1];

		if (des == NULL)
			return NULL;

		if (0 == MultiByteToWideChar(charset, 0, src, src_len, des, des_len))
		{
			delete [] des;
			return NULL;
		}

		des[des_len] = 0;

		return des;
	}

	char* _wchar_to_char(const wchar_t* src, int src_len, int charset, int& des_len)
	{
		if (src == NULL || 0 == src_len)
		{
			return NULL;
		}

		if (src_len==-1)
		{
			src_len = (DWORD)wcslen(src);
		}

		des_len = WideCharToMultiByte(charset, NULL, src, src_len, NULL, NULL, NULL, NULL);

		if(des_len==0)
		{
			return NULL;
		}

		char * des = new char[des_len + 1];
		memset(des, 0, des_len+1);

		if (des == NULL)
		{
			return NULL;
		}

		if(0 == WideCharToMultiByte(charset, NULL, src, src_len, des, des_len,NULL,NULL))
		{
			delete [] des;
			return NULL;
		}

		des[des_len] = 0;
		return	des;
	}

	wchar_t* _char_to_wchar(const char* src, int src_len, int charset)
	{
		if (src == NULL)
		{
			return NULL;
		}

		int des_len = MultiByteToWideChar(charset, 0, src, src_len, NULL, NULL );

		if (des_len == 0)
			return NULL;

		wchar_t* des = new wchar_t[des_len + 1];

		if (des == NULL)
			return NULL;

		if (0 == MultiByteToWideChar(charset, 0, src, src_len, des, des_len))
		{
			delete [] des;
			return NULL;
		}

		des[des_len] = 0;

		return des;
	}

	char* _wchar_to_char(const wchar_t* src, int src_len, int charset)
	{
		if (src == NULL)
		{
			return NULL;
		}

		if (src_len==-1)
		{
			src_len = (DWORD)wcslen(src);
		}

		int des_len = WideCharToMultiByte(charset, NULL, src, src_len, NULL, NULL, NULL, NULL);

		if(des_len==0)
		{
			return NULL;
		}

		char * des = new char[des_len + 1];
		memset(des, 0, des_len+1);

		if (des == NULL)
		{
			return NULL;
		}

		if(0 == WideCharToMultiByte(charset, NULL, src, src_len, des, des_len,NULL,NULL))
		{
			delete [] des;
			return NULL;
		}

		des[des_len] = 0;
		return	des;
	}

	wstring StringToWstring(const string& src, int charset)
	{
		int des_len = 0;
		wchar_t* des = _char_to_wchar(src.c_str(), src.length(), charset, des_len);
		wstring des_string(des, des_len);
		delete []des;
		return des_string;
	}

	string WstringToString(const wstring& src, int charset)
	{
		int des_len = 0;
		char* des = _wchar_to_char(src.c_str(), src.length(), charset, des_len);
		string des_string(des, des_len);
		delete []des;
		return des_string;
	}

	string ConvertString( const string& src, int old_charset, int new_charset)
	{
		wstring des = StringToWstring(src, old_charset);
		return WstringToString(des, new_charset);
	}

}

