#ifndef mvcgame_AssetStreamManager_hpp
#define mvcgame_AssetStreamManager_hpp

#include <mvcgame/asset/IStreamLoader.hpp>

#include <memory>
#include <vector>
#include <map>

namespace mvcgame {

    /**
     * This class maintains a list of asset stream loaders.
     */
    class AssetStreamManager
    {
    private:
        typedef IStreamLoader Loader;
        typedef Loader::Callback Callback;
        typedef std::vector<std::unique_ptr<Loader>> Loaders;

        Loaders _loaders;
    public:
        AssetStreamManager();

        /**
         * Registers a stream loader
         */
        void addLoader(std::unique_ptr<Loader> loader);

        /**
         * Tries to load an asset
         * this function will ask all the stream loaders for possible
         * streams and call the callback on them. If the callback
         * responds true it will stop and return true. It will return
         * false otherwise.
         */
        bool load(const std::string& name, Callback callback);
    };
}

#endif