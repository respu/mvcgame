

#ifndef mvcgame_TextureAtlas_hpp
#define mvcgame_TextureAtlas_hpp

#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/texture/TextureRegion.hpp>

#include <vector>
#include <string>
#include <memory>

namespace mvcgame {

    class TextureAtlas
    {
    public:
        typedef TextureRegion Region;
        typedef std::vector<Region> RegionList;
    private:
        std::shared_ptr<const Texture> _texture;
        RegionList _regions;
    public:
        TextureAtlas();

        std::shared_ptr<const Texture> getTexture() const;
        void setTexture(std::shared_ptr<const Texture> texture);
        void addRegion(const Region& region);
        RegionList& getRegions();
        const RegionList& getRegions() const;
        RegionList getRegions(const std::string& name) const;
        const Region& getRegion(const std::string& name) const;
        Region& getRegion(const std::string& name);
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const TextureAtlas& t);
}

#endif