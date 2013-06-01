
#include <mvcgame/texture/TextureRegion.hpp>
#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/base/Geometry.hpp>

namespace mvcgame {

    TextureRegion::TextureRegion() :
    x(0), y(0), width(0), height(0),
    originalWidth(0), originalHeight(0),
    offsetX(0), offsetY(0), index(0), rotate(false)
    {
    }

    TextureRegion::TextureRegion(const Texture& texture) :
    x(0), y(0), width(texture.getWidth()), height(texture.getHeight()),
    originalWidth(texture.getWidth()), originalHeight(texture.getHeight()),
    offsetX(0), offsetY(0), index(0), rotate(false)
    {
    }

    Rect TextureRegion::operator/(const Texture& t) const
    {
        return Rect((float)x/t.getWidth(), (float)y/t.getHeight(),
            (float)width/t.getWidth(), (float)height/t.getHeight());
    }

    Rect TextureRegion::operator/(const Rect& r) const
    {
        return Rect(r.origin.x+offsetX, r.origin.y+offsetY,
            r.size.width*width/originalWidth, r.size.height*height/originalHeight);
    }

    bool TextureRegion::operator<(const TextureRegion& region)
    {
        return index<region.index;
    }

    std::ostream& operator<<(std::ostream& os, const TextureRegion& t)
    {
        os << "TextureRegion( " << t.name << " xy " << t.x << "x" << t.y << ", ";
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