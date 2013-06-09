

#include <mvcgame/platform/win/FilesystemBridge.hpp>

#ifdef MVCGAME_DEBUG_FILESYSTEM
#include <iostream>
#endif

#include <windows.h>
#include <algorithm>

#define DIR_SEP_WIN '\\'
#define DIR_SEP '/'

namespace mvcgame {

	std::string utf8_encode(const std::wstring &wstr)
	{
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
		std::string strTo( size_needed, 0 );
		WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
		return strTo;
	}

	// Convert an UTF8 string to a wide Unicode String
	std::wstring utf8_decode(const std::string &str)
	{
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
		std::wstring wstrTo( size_needed, 0 );
		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
		return wstrTo;
	}

    FilesystemBridge::FilesystemBridge()
    {
		HMODULE hModule = GetModuleHandleW(NULL);
		std::wstring wpath(MAX_PATH, 0);
		GetModuleFileNameW(hModule, &wpath[0], MAX_PATH);
		_exePath = utf8_encode(wpath);
		_exePath = _exePath.substr(0, _exePath.find_last_of(DIR_SEP_WIN));
    }

    std::string FilesystemBridge::fixPath(const std::string& path)
    {
        std::string p = path;
        if(p.substr(1,2) != ":/")
        {
            p = _exePath + DIR_SEP + p;
        }
		std::replace( p.begin(), p.end(), DIR_SEP_WIN, DIR_SEP);
        return p;
    }

    bool FilesystemBridge::readResource(const std::string& path, std::ifstream& in)
    {
        std::string p = fixPath(path);

#ifdef MVCGAME_DEBUG_FILESYSTEM
        std::cout << ">>>>" << std::endl;        
        std::cout << "FilesystemBridge::readResource" << std::endl;
        std::cout << path << std::endl;
        std::cout << p << std::endl;
        std::cout << "<<<<" << std::endl;
#endif
        in.open(p, std::ios::binary);
        return true;
    }

    FilesystemBridge::Paths FilesystemBridge::findResource(const std::string& name, const std::string& path)
    {
        Paths results;

		WIN32_FIND_DATA findFileData;
		std::string rpath = fixPath(path);
		std::wstring wpath = utf8_decode(rpath+"/*");
		HANDLE hFind = FindFirstFile(&wpath[0], &findFileData);

		Paths files;
		files.push_back(utf8_encode(findFileData.cFileName));

		while (FindNextFile(hFind, &findFileData))
		{
			files.push_back(utf8_encode(findFileData.cFileName));
		}

		for(const std::string& filename : files)
		{
			if(filename.find(name) != std::string::npos)
            {
                results.push_back(rpath+DIR_SEP+filename);
            }
		}

#ifdef MVCGAME_DEBUG_FILESYSTEM
        std::cout << ">>>>" << std::endl;        
        std::cout << "FilesystemBridge::findResource" << std::endl;
        std::cout << name << " " << path << std::endl;
        for(const std::string& r : results)
        {
            std::cout << r << std::endl;
        }
        std::cout << "<<<<" << std::endl;
#endif

        return results;
    }

}