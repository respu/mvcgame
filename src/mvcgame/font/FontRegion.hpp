

#ifndef mvcgame_FontRegion_hpp
#define mvcgame_FontRegion_hpp

#include <mvcgame/texture/TextureRegion.hpp>

namespace mvcgame {

    class Rect;
    class Texture;
    class Size;

    class FontRegion : public TextureRegion
    {
    public:
        float advanceX;

        FontRegion();
        FontRegion(const Texture& texture);
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const FontRegion& t);
}

#endif