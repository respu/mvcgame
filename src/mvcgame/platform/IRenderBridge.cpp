
#include <mvcgame/platform/IRenderBridge.hpp>
#include <mvcgame/texture/TextureRegion.hpp>

namespace mvcgame {

    void IRenderBridge::beforeDraw()
    {

    }

    void IRenderBridge::afterDraw()
    {
        
    }

    IRenderBridge::TexturePoints IRenderBridge::getTextureRectPoints(const Texture& texture, const Rect& rect, const TextureRegion& region)
    {
        Rect trect = region / texture;
        Rect rrect = region / rect;
        TexturePoints points(4);

        points.push_back(TexturePoint{
            Point(rrect.origin.x, rrect.origin.y),
            Point(trect.origin.x, trect.origin.y)
        });
        points.push_back(TexturePoint{
            Point(rrect.origin.x+rrect.size.width, rrect.origin.y),
            Point(trect.origin.x+trect.size.width, trect.origin.y)
        });
        points.push_back(TexturePoint{
            Point(rrect.origin.x+rrect.size.width, rrect.origin.y+rrect.size.height),
            Point(trect.origin.x+trect.size.width, trect.origin.y+trect.size.height)
        });
        points.push_back(TexturePoint{
            Point(rrect.origin.x, rrect.origin.y+rrect.size.height),
            Point(trect.origin.x, trect.origin.y+trect.size.height)
        });

        if(region.rotate)
        {
            std::swap(points[0].texture, points[3].texture);
            std::swap(points[1].texture, points[2].texture);
        }
        return points; 
    }

    void IRenderBridge::drawTexture(std::shared_ptr<const Texture> texture, const Rect& rect, const TextureRegion& region)
    {
        drawTexture(texture, getTextureRectPoints(*texture, rect, region));
    }

    void IRenderBridge::drawTexture(std::shared_ptr<const Texture> texture, const Rect& rect)
    {
        drawTexture(texture, rect, TextureRegion(*texture));
    }
}