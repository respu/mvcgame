#ifndef mvcgame_BaseAssetsManager_hpp
#define mvcgame_BaseAssetsManager_hpp

#include <mvcgame/asset/IStreamLoader.hpp>

#include <memory>
#include <vector>
#include <map>

namespace mvcgame {

    /**
     * This is a base for the assets manager. It maintains a list
     * of asset stream loaders.
     */
    class BaseAssetsManager
    {
    private:
        typedef IStreamLoader Loader;
        typedef Loader::Callback Callback;
        typedef std::vector<std::unique_ptr<Loader>> Loaders;

        Loaders _loaders;
    public:
        BaseAssetsManager();
        virtual ~BaseAssetsManager();

        /**
         * Registers a stream loader
         */
        void addStreamLoader(std::unique_ptr<Loader> loader);

        /**
         * Tries to load an asset
         * this function will ask all the stream loaders for possible
         * streams and call the callback on them. If the callback
         * responds true it will stop and return true. It will return
         * false otherwise.
         */
        bool loadStream(const std::string& name, Callback callback);
    };
}

#endif