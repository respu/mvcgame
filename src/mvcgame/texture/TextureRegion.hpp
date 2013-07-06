

#ifndef mvcgame_TextureRegion_hpp
#define mvcgame_TextureRegion_hpp

#include <iostream>
#include <string>

namespace mvcgame {

    class Rect;
    class Texture;
    class Size;

    class TextureRegion
    {
    public:
        enum class Origin
        {
            TopLeft,
            BottomLeft,
            TopRight,
            BottomRight
        };

        std::string name;
        unsigned x;
        unsigned y;
        unsigned width;
        unsigned height;
        unsigned originalWidth;
        unsigned originalHeight;
        int offsetX;
        int offsetY;
        unsigned index;
        bool rotate;
        Origin origin;

        TextureRegion();
        explicit TextureRegion(const Texture& texture);

        /**
         * Returns a unitary rectangle (as if the texture was size 1x1)
         * and with coordinates from the bottom left corner
         */
        Rect operator/(const Texture& t) const;

        /**
         * given a rect to draw the region in
         * corrects it depending on the original size and offset
         */
        Rect operator/(const Rect& r) const;

        bool operator<(const TextureRegion& region) const;
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const TextureRegion& t);
}

#endif