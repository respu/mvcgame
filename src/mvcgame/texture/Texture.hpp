

#ifndef mvcgame_Texture_hpp
#define mvcgame_Texture_hpp

#include <memory>
#include <cstdint>
#include <mvcgame/base/Geometry.hpp>

namespace mvcgame {

    class Texture
    {
    private:
        std::unique_ptr<uint8_t> _data;
        std::size_t _length;
        Size _size;
        bool _alpha;
    public:
        Texture(std::unique_ptr<uint8_t> data, std::size_t length, const Size& size, bool hasAlpha);
        
        const uint8_t* getData() const;
        std::size_t getLength() const;
        const Size& getSize() const;
        bool hasAlpha() const;
        unsigned getComponents() const;
    };

}

#endif