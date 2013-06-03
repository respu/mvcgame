
#include <mvcgame/asset/FileStreamLoader.hpp>
#include <mvcgame/platform/IFilesystemBridge.hpp>
#include <iostream>
namespace mvcgame {

    FileStreamLoader::FileStreamLoader(IFilesystemBridge& bridge) :
    _bridge(bridge)
    {
    }

    bool FileStreamLoader::load(const std::string& name, Callback callback)
    {
        Paths results;
        for(const std::string& path : _paths)
        {
            Paths pathResults = _bridge.findResource(name, path);
            results.insert(results.end(), pathResults.begin(), pathResults.end());
        }
        for(const std::string& path : results)
        {
            std::ifstream in;
            if(_bridge.readResource(path, in))
            {
                std::string tag;
                std::size_t pos = path.find_last_of('.');
                if(pos != std::string::npos)
                {
                    tag = path.substr(pos+1);
                }
                if(callback(in, tag))
                {
                    return true;
                }
            }
        }
        return false;
    }

    void FileStreamLoader::addPath(const std::string& path)
    {
        _paths.push_back(path);
    }

}