#ifndef COMMON_PATH_H
#define COMMON_PATH_H

#include <vector>
#include <string>
#include <windows.h>
#include "winapi.hpp"

using namespace std;

namespace common{

#define get_exe_dir				GetExeDir<char>
#define get_current_dir			GetCurrentDir<char>
#define get_path_folder_name	GetPathFolderName<char>
#define get_path_directory		GetPathDirectory<char>
#define get_path_filename		GetPathFilename<char>
#define get_path_extension		GetPathExtension<char>
#define get_path_fullname		GetPathFullname<char>
#define get_path_drive			GetPathDrive<char>

	//************************************
	// Method:    GetExeDir
	// FullName:  common<T>::GetExeDir
	// Access:    public 
	// Returns:   
	// Qualifier:
	// Parameter: int parentLevel
	//************************************
	template<typename T>
	basic_string<T> GetExeDir(int parentLevel = 0)
	{
		T path[MAX_PATH] = {0};
		if (!GETMODULEFILENAME(T)(NULL, path, sizeof(path)))
			return LITERAL(T, "");

		T* tmp = STRRCHR(T)(path, '\\');
		if (tmp)
			*(tmp + 1) = '\0';

		while (parentLevel--) {
			*tmp = '\0';
			tmp = STRRCHR(T)(path, '\\');
			if (!tmp) {
				path[STRLEN(T)(path)] = '\\';
				break;
			}else
				*(tmp + 1) = '\0';
		}

		return basic_string<T>(path);
	}

	//************************************
	// Method:    GetCurrentDir
	// FullName:  common<T>::GetCurrentDir
	// Access:    public 
	// Returns:   
	// Qualifier:
	//************************************
	template<typename T>
	basic_string<T> GetCurrentDir()
	{
		T path[FILENAME_MAX] = {0};
		//if (!_getcwd(path, sizeof(path)))
		if (!GETCURRENTDIRECTORY(T)(FILENAME_MAX, path))
			return LITERAL(T, "");
		path[STRLEN(T)(path)] = '\\';
		return basic_string<T>(path);
	}

	//************************************
	// Method:    GetPathFolderName
	// FullName:  common<T>::GetPathFolderName
	// Access:    public 
	// Returns:   
	// Qualifier:
	// Parameter: const basic_string<T> & path
	//************************************
	template<typename T>
	basic_string<T> GetPathFolderName(const T* path)
	{
		typedef basic_string<T> str;

		T drive[_MAX_DRIVE];
		T dir[_MAX_DIR];
		T fname[_MAX_FNAME];
		T ext[_MAX_EXT];
		SPLITPATH_S(T)(path, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);

		str folderName;
		str directory(dir);
		str::size_type end = directory.find_last_of('\\');
		if (end != str::npos) {
			str tmp = directory.substr(0, end);
			str::size_type beg = tmp.find_last_of('\\');
			if (beg != str::npos && beg < end)
				folderName = directory.substr(beg + 1, end - beg - 1);
		}
		if (folderName.empty() && STRLEN(T)(drive) != 0)
			folderName.append(1, drive[0]);

		return folderName;
	}

	//************************************
	// Method:    GetPathDirectory
	// FullName:  common<T>::GetPathDirectory
	// Access:    public 
	// Returns:   
	// Qualifier:
	// Parameter: const basic_string<T> & path
	//************************************
	template<typename T>
	basic_string<T> GetPathDirectory(const T* path)
	{
		typedef basic_string<T> str;
		T drive[_MAX_DRIVE];
		T dir[_MAX_DIR];
		T fname[_MAX_FNAME];
		T ext[_MAX_EXT];
		SPLITPATH_S(T)(path, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
		return str(drive) + str(dir);
	}

	//************************************
	// Method:    GetPathFilename
	// FullName:  common<T>::GetPathFilename
	// Access:    public 
	// Returns:   
	// Qualifier:
	// Parameter: const basic_string<T> & path
	//************************************
	template<typename T>
	basic_string<T> GetPathFilename(const T* path)
	{
		T drive[_MAX_DRIVE];
		T dir[_MAX_DIR];
		T fname[_MAX_FNAME];
		T ext[_MAX_EXT];
		SPLITPATH_S(T)(path, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
		return basic_string<T>(fname);
	}

	//************************************
	// Method:    GetPathExtension
	// FullName:  common<T>::GetPathExtension
	// Access:    public 
	// Returns:   
	// Qualifier:
	// Parameter: const basic_string<T> & path
	//************************************
	template<typename T>
	basic_string<T> GetPathExtension(const T* path)
	{
		T drive[_MAX_DRIVE];
		T dir[_MAX_DIR];
		T fname[_MAX_FNAME];
		T ext[_MAX_EXT];
		SPLITPATH_S(T)(path, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
		return basic_string<T>(ext);
	}

	//************************************
	// Method:    GetPathFullname
	// FullName:  common<T>::GetPathFullname
	// Access:    public 
	// Returns:   
	// Qualifier:
	// Parameter: const T * path
	//************************************
	template<typename T>
	basic_string<T> GetPathFullname(const T* path)
	{	
		T drive[_MAX_DRIVE];
		T dir[_MAX_DIR];
		T fname[_MAX_FNAME];
		T ext[_MAX_EXT];
		SPLITPATH_S(T)(path, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
		return basic_string<T>(fname) + basic_string<T>(ext);
	}

	//************************************
	// Method:    GetPathFullname
	// FullName:  common<T>::GetPathFullname
	// Access:    public 
	// Returns:   
	// Qualifier:
	// Parameter: const T * path
	//************************************
	template<typename T>
	basic_string<T> GetPathDrive(const T* path)
	{	
		T drive[_MAX_DRIVE];
		T dir[_MAX_DIR];
		T fname[_MAX_FNAME];
		T ext[_MAX_EXT];
		SPLITPATH_S(T)(path, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
		return basic_string<T>(drive);
	}
}

#endif