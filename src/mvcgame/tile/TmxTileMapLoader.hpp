
#ifndef mvcgame_TmxTileMapLoader_hpp
#define mvcgame_TmxTileMapLoader_hpp

#include <mvcgame/asset/IAssetLoader.hpp>


/**
 * @see http://code.google.com/p/tmx-parser/source/browse/trunk/TmxParser/
 */
 namespace mvcgame {

    class TileMap;

    class TmxTileMapLoader : public IAssetLoader<TileMap>
    {
    public:
        bool validate(std::istream& input) const;
        std::unique_ptr<TileMap> load(std::istream& input) const;
    };
}

#endif