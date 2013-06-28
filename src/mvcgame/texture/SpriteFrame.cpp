
#include <mvcgame/texture/SpriteFrame.hpp>

namespace mvcgame {

    SpriteFrame::SpriteFrame()
    {
    }

    SpriteFrame::SpriteFrame(std::shared_ptr<const Texture> texture) :
    _texture(texture), _region(*texture)
    {
    }    

    SpriteFrame::SpriteFrame(std::shared_ptr<const Texture> texture, const TextureRegion& region) :
    _texture(texture), _region(region)
    {
    }

    const Texture& SpriteFrame::getTexture() const
    {
        return *_texture;
    }

    const TextureRegion& SpriteFrame::getRegion() const
    {
        return _region;
    }

    TextureRegion& SpriteFrame::getRegion()
    {
        return _region;
    }

    std::ostream& operator<<(std::ostream& os, const SpriteFrame& f)
    {
        os << "SpriteFrame(" << f.getRegion() << std::endl;
        os << f.getTexture() << ")" << std::endl;
        return os;
    }

}