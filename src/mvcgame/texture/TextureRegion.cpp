
#include <mvcgame/texture/TextureRegion.hpp>
#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/base/Geometry.hpp>

#include <algorithm>

namespace mvcgame {

    TextureRegion::TextureRegion() :
    x(0), y(0), width(0), height(0),
    originalWidth(0), originalHeight(0),
    offsetX(0), offsetY(0), index(0),
    rotate(false), origin(Origin::BottomLeft)
    {
    }

    TextureRegion::TextureRegion(const Texture& texture) :
    x(0), y(0), width(texture.getWidth()), height(texture.getHeight()),
    originalWidth(texture.getWidth()), originalHeight(texture.getHeight()),
    offsetX(0), offsetY(0), index(0), rotate(false), origin(Origin::BottomLeft)
    {
    }

    Rect TextureRegion::operator/(const Texture& t) const
    {
        float rw = rotate?height:width;
        float rh = rotate?width:height;

        Rect r((float)x/t.getWidth(), (float)y/t.getHeight(),
            rw/t.getWidth(), rh/t.getHeight());

        if(origin == Origin::TopLeft || origin == Origin::TopRight)
        {
            r.origin.y = 1.0f - r.origin.y - r.size.height;            
        }
        if(origin == Origin::BottomRight || origin == Origin::TopRight)
        {
            r.origin.x = 1.0f - r.origin.x - r.size.width;
        }

        return r;
    }

    Rect TextureRegion::operator/(const Rect& r) const
    {
        Rect tr(r.origin.x+offsetX, r.origin.y+offsetY,
            r.size.width*width/originalWidth, r.size.height*height/originalHeight);

        if(rotate)
        {
            std::swap(tr.origin.x, tr.origin.y);
            std::swap(tr.size.width, tr.size.height);
        }

        return tr;
    }

    bool TextureRegion::operator<(const TextureRegion& region) const
    {
        return index < region.index;
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