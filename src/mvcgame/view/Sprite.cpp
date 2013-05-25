
#include <mvcgame/view/Sprite.hpp>
#include <mvcgame/platform/IViewBridge.hpp>

namespace mvcgame {

    Sprite::Sprite()
    {
    }

    Sprite::Sprite(std::shared_ptr<const Texture> texture)
    {
        setTexture(texture);
    }
    
    const Texture& Sprite::getTexture() const
    {
        return *_texture;
    }

    void Sprite::setTexture(std::shared_ptr<const Texture> texture)
    {
        _texture = texture;
    }

    void Sprite::draw()
    {
        getBridge().drawTexture(getFrame().size, *_texture);
    }

}