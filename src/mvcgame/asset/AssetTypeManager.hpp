#ifndef mvcgame_AssetTypeManager_hpp
#define mvcgame_AssetTypeManager_hpp

#include <mvcgame/asset/BaseAssetsManager.hpp>
#include <mvcgame/asset/IAssetLoader.hpp>

#include <memory>
#include <vector>
#include <map>
#include <stdexcept>

namespace mvcgame {

    /**
     * This class loads assets of a given type. It maintains a list of 
     * loaders of the asset type and a reference to the main assets manager.
     *
     * To load an asset it will ask the asset stream loaders of the main manager
     * for possible streams, then it will ask the list of asset loaders if they can
     * load the given streams.
     *
     * The tag value can be set by the IStreamLoader
     * and similar to a file extension
     */
    template<typename Asset>
    class AssetTypeManager
    {
    private:
        typedef IAssetLoader<Asset> Loader;
        typedef std::vector<std::unique_ptr<Loader>> Loaders;
        typedef std::map<std::string, Loaders> LoaderMap;

        BaseAssetsManager& _mng;
        LoaderMap _loaders;

        bool doLoadStream(std::istream& in, const Loaders& loaders, std::unique_ptr<Asset>* asset)
        {
            for(const std::unique_ptr<Loader>& loader : loaders)
            {
                in.seekg(0, std::ios::beg);
                if(loader->validate(in))
                {
                    in.seekg(0, std::ios::beg);
                    *asset = loader->load(in);
                    if(*asset)
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        bool loadStream(std::istream& in, const std::string& tag, std::unique_ptr<Asset>* asset)
        {
            typename LoaderMap::const_iterator itr = _loaders.find(tag);
            if(itr != _loaders.end() && doLoadStream(in, itr->second, asset))
            {
                return true;
            }
            itr = _loaders.find("");
            if(itr != _loaders.end() && doLoadStream(in, itr->second, asset))
            {
                return true;
            }
            return false;
        }

    public:
        AssetTypeManager(BaseAssetsManager& mng) :
        _mng(mng)
        {
        }

        void add(std::unique_ptr<Loader> loader, const std::string& tag="")
        {
            _loaders[tag].push_back(std::move(loader));
        }

        std::unique_ptr<Asset> load(const std::string& name)
        {
            std::unique_ptr<Asset> asset = nullptr;
            bool success = _mng.loadStream(name, std::bind(&AssetTypeManager<Asset>::loadStream,
                this, std::placeholders::_1, std::placeholders::_2, &asset));
			if(!success)
			{
				throw std::runtime_error("Could not load asset");
			}
            return std::move(asset);
        }

    };
}

#endif