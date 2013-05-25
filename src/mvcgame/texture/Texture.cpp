
#include <mvcgame/texture/Texture.hpp>
#include <cassert>

namespace mvcgame
{

    Texture::Texture(std::unique_ptr<uint8_t> data, std::size_t length, const Size& size, bool alpha) :
    _data(std::move(data)), _length(length), _size(size), _alpha(alpha)
    {
    }

    const uint8_t* Texture::getData() const
    {
        return _data.get();
    }

    std::size_t Texture::getLength() const
    {
        return _length;
    }    

    const Size& Texture::getSize() const
    {
        return _size;
    }

    bool Texture::hasAlpha() const
    {
        return _alpha;
    }

    unsigned Texture::getComponents() const
    {
        return hasAlpha() ? 4 : 3;
    }

}