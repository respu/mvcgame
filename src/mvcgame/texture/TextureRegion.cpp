
#include <mvcgame/texture/TextureRegion.hpp>
#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/base/Geometry.hpp>

namespace mvcgame {

    TextureRegion::TextureRegion() :
    x(0), y(0), width(0), height(0)
    {
    }

    TextureRegion::TextureRegion(const Texture& texture) :
    x(0), y(0), width(texture.getWidth()), height(texture.getHeight())
    {
    }

    TextureRegion::TextureRegion(unsigned px, unsigned py, unsigned pwidth, unsigned pheight) :
    x(px), y(py), width(pwidth), height(pheight)
    {
    }

    Rect TextureRegion::operator/(const Texture& t) const
    {
        return Rect((float)x/t.getWidth(), (float)y/t.getHeight(),
            (float)width/t.getWidth(), (float)height/t.getHeight());
    }

    Rect TextureRegion::operator/(const Size& s) const
    {
        return Rect(x/s.width, y/s.height, width/s.width, height/s.height);
    }

    std::ostream& operator<<(std::ostream& os, const TextureRegion& t)
    {
        os << "TextureRegion( " << t.x << "x" << t.y << ", ";
        os << t.width << "x" << t.height << ")";
        return os;
    }
}