

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
        std::string name;
        unsigned x;
        unsigned y;
        unsigned width;
        unsigned height;
        unsigned originalWidth;
        unsigned originalHeight;
        unsigned offsetX;
        unsigned offsetY;
        unsigned index;
        bool rotate;

        TextureRegion();
        TextureRegion(const Texture& texture);

        Rect operator/(const Texture& t) const;
        Rect operator/(const Rect& r) const;

        bool operator<(const TextureRegion& region);
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const TextureRegion& t);
}

#endif