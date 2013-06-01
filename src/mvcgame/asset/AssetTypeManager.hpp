#ifndef mvcgame_AssetTypeManager_hpp
#define mvcgame_AssetTypeManager_hpp

#include <mvcgame/asset/BaseAssetsManager.hpp>
#include <mvcgame/asset/IAssetLoader.hpp>

#include <memory>
#include <vector>
#include <map>

namespace mvcgame {

    /**
     * This class loads assets of a given type. It maintains a list of 
     * loaders of the asset type and a reference to the main assets manager.
     *
     * To load an asset it will ask the asset stream loaders of the main manager
     * for possible streams, then it will ask the list of asset loaders if they can
     * load the given streams.
     */
    template<typename Asset>
    class AssetTypeManager
    {
    private:
        typedef IAssetLoader<Asset> Loader;
        typedef std::vector<std::unique_ptr<Loader>> Loaders;

        BaseAssetsManager& _mng;
        Loaders _loaders;

        bool loadStream(std::istream& in, std::unique_ptr<Asset>* asset)
        {
            for(std::unique_ptr<Loader>& loader : _loaders)
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

    public:
        AssetTypeManager(BaseAssetsManager& mng) :
        _mng(mng)
        {
        }

        void add(std::unique_ptr<Loader> loader)
        {
            _loaders.push_back(std::move(loader));
        }

        std::unique_ptr<Asset> load(const std::string& name)
        {
            std::unique_ptr<Asset> asset;
            _mng.loadStream(name, std::bind(&AssetTypeManager<Asset>::loadStream, this, std::placeholders::_1, &asset));
            return std::move(asset);
        }

    };
}

#endif