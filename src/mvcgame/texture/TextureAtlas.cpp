
#include <mvcgame/texture/TextureAtlas.hpp>
#include <mvcgame/texture/Texture.hpp>

namespace mvcgame {

    TextureAtlas::TextureAtlas()
    {
    }

    std::shared_ptr<const Texture> TextureAtlas::getTexture() const
    {
        return _texture;
    }    

    void TextureAtlas::setTexture(std::shared_ptr<const Texture> texture)
    {
        _texture = texture;
    }

    void TextureAtlas::addRegion(const Region& region)
    {
        _regions.push_back(region);
    }

    TextureAtlas::RegionList& TextureAtlas::getRegions()
    {
        return _regions;
    }

    const TextureAtlas::RegionList& TextureAtlas::getRegions() const
    {
        return _regions;
    }

    TextureAtlas::RegionList TextureAtlas::getRegions(const std::string& name) const
    {
        RegionList regions;
        for(const TextureRegion& region : getRegions())
        {
            if(region.name == name)
            {
                regions.push_back(region);
            }
        }
        return regions;
    }

    std::ostream& operator<<(std::ostream& os, const TextureAtlas& t)
    {
        os << "TextureAtlas( " << std::endl;
        if(t.getTexture())
        {
            os << *t.getTexture() << std::endl;
        }
        for(const TextureRegion& region : t.getRegions())
        {
            os << region << std::endl;
        }

        os << ")";
        return os;
    }

}
