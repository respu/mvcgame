

#ifndef mvcgame_TextureAtlas_hpp
#define mvcgame_TextureAtlas_hpp

#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/texture/TextureRegion.hpp>

#include <vector>
#include <string>

namespace mvcgame {

    class TextureAtlas
    {
    public:
        typedef TextureRegion Region;
        typedef std::vector<Region> RegionList;
    private:
        std::string _textureName;
        RegionList _regions;
    public:
        TextureAtlas();

        const std::string& getTextureName() const;
        void setTextureName(const std::string& name);
        void addRegion(const Region& region);
        RegionList& getRegions();
        const RegionList& getRegions() const;
        RegionList getRegions(const std::string& name) const;
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const TextureAtlas& t);
}

#endif