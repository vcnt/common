#ifndef STRING_HPP
#define STRING_HPP

#include <vector>
#include <tuple>
using namespace std;

#include "winapi.hpp"

namespace Common{

#define replace_all				ReplaceAll<char>
#define get_replace_all			GetReplaceAll<char>
#define replace_all_distinct	ReplaceAllDistinct<char>
#define strip					Strip<char>
#define get_strip				GetStrip<char>
#define quote					Quote<char>
#define get_quote				GetQuote<char>
#define unquote					Unquote<char>
#define has_quote				HasQuote<char>
#define split					Split<char>
#define joint					Joint<char>
#define format_string			FormatString<char>
#define format_append			FormatAppend<char>
#define output_debug_message	OutputDebugMessage<char>

	//replace "ab" with "a", result : "abb" => "a"
	template<typename T>
	basic_string<T>& ReplaceAll(basic_string<T>& str, const basic_string<T>& old, const basic_string<T>& newly)
	{
		typedef basic_string<T> Str;
		while (true)
		{
			Str::size_type pos(0);
			if ((pos = str.find(old)) != Str::npos)
				str.replace(pos, old.length(), newly);
			else
				break;
		}
		return str;
	}

	template<typename T>
	basic_string<T> GetReplaceAll(basic_string<T> str, const basic_string<T>& old, const basic_string<T>& newly)
	{
		return ReplaceAll<T>(str, old, newly);
	}

	//replace "ab" with "a", result : "abb" => "ab"
	template<typename T>
	basic_string<T>& ReplaceAllDistinct(basic_string<T>& str, const basic_string<T>& old, const basic_string<T>& newly)
	{
		typedef basic_string<T> Str;
		for (Str::size_type pos(0); pos != Str::npos; pos += newly.length())
		{
			if ((pos = str.find(old, pos)) != Str::npos)
				str.replace(pos, old.length(), newly);
			else
				break;
		}
		return str;
	}

	template<typename T>
	basic_string<T>& Strip(basic_string<T>& str, const T* trim = LITERAL(T, " "))
	{
		if (!trim)
			return str;

		str.erase(0, str.find_first_not_of(trim));
		str.erase(str.find_last_not_of(trim) + 1);
		return str;
	}

	template<typename T>
	basic_string<T> GetStrip(basic_string<T> str, const T* trim = LITERAL(T, " "))
	{
		return Strip<T>(str, trim);
	}

	template<typename T>
	tuple<T, T> _get_quote_char(T ch)
	{
		T beg, end;
		switch (ch)
		{
		case '[':
		case ']':
			beg = '[';
			end = ']';
			break;

		case '(':
		case ')':
			beg = '(';
			end = ')';
			break;

		case '{':
		case '}':
			beg = '{';
			end = '}';
			break;

		case '"':
		case '\'':
		default:
			beg = end = ch;
			break;
		}
		return make_tuple<T, T>(beg, end);
	}

	template<typename T>
	basic_string<T>& Quote(basic_string<T>& str, T ch = '"')
	{
		if (str.empty())
			return str.append(2, ch);

		tuple<T, T> chs = _get_quote_char(ch);
		T beg = std::get<0>(chs);
		T end = std::get<1>(chs);

		size_t size = str.size();
		if (str[0] == beg && str[size - 1] == end)
			return str;

		str.insert(str.begin(), 1, beg);
		str.append(1, end);
		return str;
	}

	template<typename T>
	basic_string<T> GetQuote(basic_string<T> str, T ch = '"')
	{
		return Quote<T>(str, ch);
	}

	template<typename T>
	basic_string<T>& Unquote(basic_string<T>& str, T ch = '"')
	{
		if (str.size() <= 1)
			return str;

		tuple<T, T> chs = _get_quote_char(ch);
		T beg = std::get<0>(chs);
		T end = std::get<1>(chs);

		if (str[0] == beg && str[str.size() - 1] == end)
			str = str.substr(1, str.size() - 2);

		return str;
	}

	template<typename T>
	bool HasQuote(const basic_string<T>& str, T ch = '"')
	{
		if (str.size() <= 1)
			return false;

		tuple<T, T> chs = _get_quote_char(ch);
		T beg = std::get<0>(chs);
		T end = std::get<1>(chs);

		return str[0] == beg && str[str.size() - 1] == end;
	}

	// split "abc" with ";" , result {"abc"}
	// split "abc;" with ";" , result {"abc"}
	// split ";abc;" with ";", result {"", "abc"}, you can call Strip to trim ";" before call Split
	template<typename T>
	vector<basic_string<T>> Split(const basic_string<T>& str, const basic_string<T>& pattern)
	{
		typedef basic_string<T> Str;

		vector<Str> result;
		size_t size = str.size();
		Str::size_type pos = 0;
		for(size_t i = 0; i < size && pos != Str::npos; i++)
		{
			pos = str.find(pattern, i);
			if (pos < size || pos == Str::npos)
			{
				Str s = str.substr(i, pos - i);
				result.push_back(s);
				i = pos + pattern.size() - 1;
			}
		}
		return result;
	}

	// joint {"abc"} with ";", result "abc"
	// joint {"abc", "efg" ""} with ";" , result "abc;efg;"
	template<typename T>
	basic_string<T> Joint(const vector<basic_string<T>>& strings, const basic_string<T>& pattern)
	{
		basic_string<T> ret;
		size_t size = strings.size();
		for (size_t i = 0; i < size; i++)
		{
			ret += strings[i];
			if (i != size - 1)
				ret += pattern;
		}
		return ret;
	}

	template<typename T>
	basic_string<T> FormatString(int size, const T* fmt, ...)
	{
		T* buf = new T[size];
		va_list ap;
		va_start(ap, fmt);
		VSPRINTF_S(T)(buf, size, fmt, ap);
		va_end(ap);
		basic_string<T> ret(buf);
		delete []buf;
		return ret;
	}

	//format string is limited in 1024 characters
	template<typename T>
	basic_string<T> FormatString(const T* fmt, ...)
	{
		T buf[1024] = {0};
		va_list ap;
		va_start(ap, fmt);
		VSPRINTF_S(T)(buf, 1024, fmt, ap);
		va_end(ap);
		return basic_string<T>(buf);
	}

	template<typename T>
	basic_string<T> FormatAppend( const basic_string<T>& pre, int size, const T* fmt, ... )
	{
		T* buf = new T[size];
		va_list ap;
		va_start(ap, fmt);
		VSPRINTF_S(T)(buf, size, fmt, ap);
		va_end(ap);
		basic_string<T> append(buf);
		delete []buf;
		return basic_string<T>(pre + append);
	}

	//format string is limited in 1024 characters
	template<typename T>
	basic_string<T> FormatAppend( const basic_string<T>& pre, const T* fmt, ... )
	{
		T buf[1024] = {0};
		va_list ap;
		va_start(ap, fmt);
		VSPRINTF_S(T)(buf, 1024, fmt, ap);
		va_end(ap);
		return basic_string<T>(pre).append(buf);
	}

	template<typename T>
	void OutputDebugMessage(int size, const T* fmt, ...)
	{
		va_list ap;
		T* buf = new T[size];
		memset(buf, 0, size*sizeof(T));
		va_start(ap, fmt);
		VSPRINTF_S(T)(buf, size, fmt, ap);
		va_end(ap);
		STRCAT_S(T)(buf, size, LITERAL(T, "\n"));
		OUTPUTDEBUGSTRING(T)(buf);
		delete []buf;
	}

	//format string is limited in 1024 characters
	template<typename T>
	void OutputDebugMessage(const T* fmt, ...)
	{
		va_list ap;
		T buf[1024] = {0};
		va_start(ap, fmt);
		VSPRINTF_S(T)(buf, 1024, fmt, ap);
		va_end(ap);
		STRCAT_S(T)(buf, 1024, LITERAL(T, "\n"));
		OUTPUTDEBUGSTRING(T)(buf);
	}
}

#endif