

#ifndef mvcgame_FontAtlasPage_hpp
#define mvcgame_FontAtlasPage_hpp

#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/font/FontRegion.hpp>

#include <vector>
#include <string>

namespace mvcgame {

    class FontAtlasPage
    {
    public:
        typedef FontRegion Region;
        typedef std::vector<Region> RegionList;
    private:
        std::string _textureName;
        RegionList _regions;
    public:
        FontAtlasPage();

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
    std::ostream& operator<<(std::ostream& os, const FontAtlasPage& t);
}

#endif