
#include <mvcgame/font/FontLetter.hpp>
#include <mvcgame/font/FontInfo.hpp>
#include <mvcgame/texture/SpriteFrame.hpp>
#include <mvcgame/texture/TextureRegion.hpp>

namespace mvcgame {

    FontLetter::FontLetter()
    {
    }

    FontLetter::FontLetter(std::shared_ptr<Texture> texture) :
    _texture(texture), _region(*texture)
    {
    }    

    FontLetter::FontLetter(std::shared_ptr<Texture> texture, const FontRegion& region) :
    _texture(texture), _region(region)
    {
    }

    const Texture& FontLetter::getTexture() const
    {
        return *_texture;
    }

    Texture& FontLetter::getTexture()
    {
        return *_texture;
    }

    const FontRegion& FontLetter::getRegion() const
    {
        return _region;
    }

    FontRegion& FontLetter::getRegion()
    {
        return _region;
    }

    SpriteFrame FontLetter::getSpriteFrame(const FontInfo& info) const
    {
        TextureRegion region(_region);
        region.offsetY = info.baseHeight-region.height-region.offsetY;      
        return SpriteFrame(_texture, region);
    }

    std::ostream& operator<<(std::ostream& os, const FontLetter& f)
    {
        os << "FontLetter(" << f.getRegion() << std::endl;
        os << f.getTexture() << ")" << std::endl;
        return os;
    }

}