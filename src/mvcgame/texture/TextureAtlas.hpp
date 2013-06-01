

#ifndef mvcgame_TextureAtlas_hpp
#define mvcgame_TextureAtlas_hpp

#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/texture/TextureRegion.hpp>

#include <vector>
#include <string>

namespace mvcgame {

    class Texture;

    class TextureAtlas
    {
    public:
        typedef TextureRegion Region;
        typedef std::vector<Region> RegionList;        
    private:
        RegionList _regions;
    public:
        TextureAtlas();
        void addRegion(const Region& region);
        RegionList& getRegions();
        const RegionList& getRegions() const;
        RegionList getRegions(std::string& name) const;
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const TextureAtlas& t);
}

#endif