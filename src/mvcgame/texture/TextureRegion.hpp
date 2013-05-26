

#ifndef mvcgame_TextureRegion_hpp
#define mvcgame_TextureRegion_hpp

#include <iostream>

namespace mvcgame {

    class Rect;
    class Texture;
    class Size;

    class TextureRegion
    {
    public:
        unsigned x;
        unsigned y;
        unsigned width;
        unsigned height;

        TextureRegion();
        TextureRegion(const Texture& texture);
        TextureRegion(unsigned x, unsigned y, unsigned width, unsigned height);

        Rect operator/(const Texture& t) const;
        Rect operator/(const Size& s) const;
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const TextureRegion& t);
}

#endif