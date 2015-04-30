#ifndef WINAPI_HPP
#define WINAPI_HPP

#include <windows.h>
//http://stackoverflow.com/questions/4261673/templates-and-string-literals-and-unicode

#define LITERAL(T, x)	Winapi::LiteralTraits<T>::choose(x, L##x)

#define SPLITPATH_S(T)			Winapi::FuncTraits<T>::_split_path()
#define GETMODULEFILENAME(T)	Winapi::FuncTraits<T>::_get_module_file_name()
#define STRRCHR(T)				Winapi::FuncTraits<T>::_strrchr()
#define STRLEN(T)				Winapi::FuncTraits<T>::_strlen()
#define STRCAT_S(T)				Winapi::FuncTraits<T>::_strcat_s()
#define GETCURRENTDIRECTORY(T)	Winapi::FuncTraits<T>::_get_current_directory()
#define VSPRINTF_S(T)			Winapi::FuncTraits<T>::_vsprintf_s()
#define OUTPUTDEBUGSTRING(T)	Winapi::FuncTraits<T>::_OutputDebugString()

namespace Winapi{
	/*literal choose*/
	template<typename T>
	struct LiteralTraits{};

	template<>
	struct LiteralTraits<char>
	{
		static const char* choose(const char* narrow, const wchar_t* wide) {return narrow;}
		//static char choose(char narrow, wchar_t wide) {return narrow;}
	};

	template<>
	struct LiteralTraits<wchar_t>
	{
		static const wchar_t* choose(const char* narrow, const wchar_t* wide) {return wide;}
		//static wchar_t choose(char narrow, wchar_t wide) {return wide;}
	};

	/*function unicode & ascii*/
	template<typename T>
	struct FuncType
	{
		typedef errno_t /*__cdecl*/ (*func_splitpath_s)(const T* _FullPath, 
			T * _Drive, size_t _DriveSize, T * _Dir, size_t _DirSize, 
			T* _Filename, size_t _FilenameSize, T* _Ext, size_t _ExtSize);
		typedef DWORD (WINAPI *func_GetModuleFileName)(HMODULE hModule, T* lpFilename, DWORD nSize);
		typedef /*inline*/ T* /*__CRTDECL*/ (*func_strrchr)(T * _Str, int _Ch);
		typedef size_t /*__cdecl*/ (*func_strlen)(const T * _Str);
		typedef errno_t /*__cdecl*/ (*func_strcat_s)(T* _Dst, size_t _SizeInBytes, const T* _Src);
		typedef DWORD (WINAPI *func_GetCurrentDirectory)(DWORD nBufferLength, T* lpBuffer);
		typedef int /*__cdecl*/ (*func_vsprintf_s)(T * _DstBuf, size_t _SizeInBytes, const T * _Format, va_list _ArgList);
		typedef VOID (WINAPI *func_OutputDebugString)(const T* lpOutputString);
	};

	template<typename T>
	struct FuncTraits{
	};

	template<>
	struct FuncTraits<char>
	{
		static FuncType<char>::func_splitpath_s _split_path(){return _splitpath_s;}
		static FuncType<char>::func_GetModuleFileName _get_module_file_name(){return GetModuleFileNameA;}
		static FuncType<char>::func_strrchr _strrchr(){return strrchr;}
		static FuncType<char>::func_strlen _strlen(){return strlen;};
		static FuncType<char>::func_strcat_s _strcat_s(){return strcat_s;}
		static FuncType<char>::func_GetCurrentDirectory _get_current_directory(){return GetCurrentDirectoryA;}
		static FuncType<char>::func_vsprintf_s _vsprintf_s(){return vsprintf_s;}
		static FuncType<char>::func_OutputDebugString _OutputDebugString(){return OutputDebugStringA;}
	};

	template<>
	struct FuncTraits<wchar_t>
	{
		static FuncType<wchar_t>::func_splitpath_s _split_path(){return _wsplitpath_s;}
		static FuncType<wchar_t>::func_GetModuleFileName _get_module_file_name() {return GetModuleFileNameW;}
		//wcsrchr, strrchr 第二个调用参数不一样，不能类型参数化，强制转换一下；另外wcsrchr具有两个重载函数，先确定重载版本，再强制转换, vs才不会报错
		static FuncType<wchar_t>::func_strrchr _strrchr(){return (wchar_t* (*)(wchar_t*, int))(wchar_t* (*)(wchar_t*, wchar_t))wcsrchr;}
		static FuncType<wchar_t>::func_strlen _strlen(){return wcslen;} 
		static FuncType<wchar_t>::func_strcat_s _strcat_s(){return wcscat_s;}
		//errno_t __cdecl wcscat_s(_Inout_z_cap_(_SizeInWords) wchar_t * _Dst, _In_ rsize_t _SizeInWords, _In_z_ const wchar_t * _Src)

		static FuncType<wchar_t>::func_GetCurrentDirectory _get_current_directory(){return GetCurrentDirectoryW;}
		static FuncType<wchar_t>::func_vsprintf_s _vsprintf_s(){return vswprintf_s;}
		static FuncType<wchar_t>::func_OutputDebugString _OutputDebugString(){return OutputDebugStringW;}
	};

}


#endif
