
#include <mvcgame/font/FontRegion.hpp>

    
namespace mvcgame {

    FontRegion::FontRegion() :
    advanceX(0.0)
    {
    }

    FontRegion::FontRegion(const Texture& texture) :
    TextureRegion(texture), advanceX(0.0)
    {
    }

    std::ostream& operator<<(std::ostream& os, const FontRegion& t)
    {
        os << "FontRegion(" << t.name << " xy " << t.x << "x" << t.y << ", ";
        os << "size " << t.width << "x" << t.height << ", ";
        os << "offset " << t.offsetX << "x" << t.offsetY << ", ";
        os << "original " << t.originalWidth << "x" << t.originalHeight;
        if(t.rotate)
        {
            os << " rotate";
        }
        os << ")";
        return os;
    }

}