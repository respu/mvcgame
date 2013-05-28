
#include <mvcgame/view/Sprite.hpp>
#include <mvcgame/platform/IRenderBridge.hpp>

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
        if(_texture)
        {
            getBridge().drawTexture(getFrame().size, *_texture);
        }
    }

}