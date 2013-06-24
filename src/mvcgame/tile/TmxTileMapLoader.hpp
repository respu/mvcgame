
#ifndef mvcgame_TmxTileMapLoader_hpp
#define mvcgame_TmxTileMapLoader_hpp

#include <mvcgame/asset/IAssetLoader.hpp>

/**
 * @see http://code.google.com/p/tmx-parser/source/browse/trunk/TmxParser/
 * @see https://github.com/bjorn/tiled/wiki/TMX-Map-Format
 */
 namespace mvcgame {

    class TileMap;
    class BaseAssetsManager;

    class TmxTileMapLoader : public IAssetLoader<TileMap>
    {
    private:
        BaseAssetsManager* _sourceLoader;
    public:

        TmxTileMapLoader();

        /**
         * Set the stream loader to load external source files
         */
        void setSourceLoader(BaseAssetsManager& loader);

        bool validate(std::istream& input) const;
        std::unique_ptr<TileMap> load(std::istream& input) const;
    };
}

#endif