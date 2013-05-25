

#ifndef mvcgame_Texture_hpp
#define mvcgame_Texture_hpp

#include <memory>
#include <cstdint>

namespace mvcgame {

    class Texture
    {
    private:
        std::unique_ptr<uint8_t []> _data;
        std::size_t _size;
    public:
        Texture(std::unique_ptr<uint8_t []> data, std::size_t size);
        const uint8_t& operator[](std::size_t i) const;
        std::size_t size() const;
    };

}

#endif