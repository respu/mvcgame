

#ifndef mvcgame_TextureAtlas_hpp
#define mvcgame_TextureAtlas_hpp

#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/texture/TextureRegion.hpp>

#include <map>
#include <string>

namespace mvcgame {

    class Texture;

    class TextureAtlas
    {
    public:
        typedef TextureRegion Region;
    private:
        typedef std::map<std::string, Region> RegionMap;
        RegionMap _regions;
    public:
        TextureAtlas();
        void setRegion(const std::string& name, const Region& region);
        const Region& getRegion(const std::string& name) const;
        bool hasRegion(const std::string& name) const;
    };

}

#endif