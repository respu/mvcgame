

#ifndef mvcgame_FontAtlasPage_hpp
#define mvcgame_FontAtlasPage_hpp

#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/font/FontRegion.hpp>

#include <vector>
#include <string>
#include <memory>

namespace mvcgame {

    class FontAtlasPage
    {
    public:
        typedef FontRegion Region;
        typedef std::vector<Region> RegionList;
    private:
        std::shared_ptr<const Texture> _texture;
        RegionList _regions;
    public:
        FontAtlasPage();

        std::shared_ptr<const Texture> getTexture() const;
        void setTexture(std::shared_ptr<const Texture> texture);
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