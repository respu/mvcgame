
#include <mvcgame/view/Sprite.hpp>

namespace mvcgame {

    Sprite::Sprite(std::shared_ptr<const Texture> texture) :
    _texture(texture)
    {
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
    }

}