
#include <mvcgame/texture/Texture.hpp>
#include <cassert>

namespace mvcgame
{

    Texture::Texture(std::unique_ptr<uint8_t> data, std::size_t length, unsigned width, unsigned height, bool alpha) :
    _data(std::move(data)), _length(length), _width(width), _height(height), _alpha(alpha)
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

    unsigned Texture::getWidth() const
    {
        return _width;
    }

    unsigned Texture::getHeight() const
    {
        return _height;
    }


    bool Texture::hasAlpha() const
    {
        return _alpha;
    }

    unsigned Texture::getComponents() const
    {
        return hasAlpha() ? 4 : 3;
    }

    std::ostream& operator<<(std::ostream& os, const Texture& t)
    {
        os << "Texture(" << t.getWidth() << "x" << t.getHeight();
        os << " len " << t.getLength() << ", comp " << t.getComponents();
        os << ")";
        return os;
    }
}