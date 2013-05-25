
#include <mvcgame/texture/Texture.hpp>
#include <cassert>

namespace mvcgame
{

    Texture::Texture(std::unique_ptr<uint8_t []> data, std::size_t size) :
    _data(std::move(data)), _size(size)
    {
    }

    const uint8_t& Texture::operator[] (std::size_t i) const
    {
        assert(i<_size);
        return _data[i];
    }

    std::size_t Texture::size() const
    {
        return _size;
    }

}