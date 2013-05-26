
#include <mvcgame/texture/TextureAtlas.hpp>

namespace mvcgame {

    TextureAtlas::TextureAtlas()
    {
    }

    void TextureAtlas::setRegion(const std::string& name, const Region& region)
    {
        _regions[name] = region;
    }

    const TextureAtlas::Region& TextureAtlas::getRegion(const std::string& name) const
    {
        return _regions.at(name);
    }

    bool TextureAtlas::hasRegion(const std::string& name) const
    {
        return _regions.find(name) != _regions.end();
    }

}
