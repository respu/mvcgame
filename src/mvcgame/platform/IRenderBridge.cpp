
#include <mvcgame/platform/IRenderBridge.hpp>
#include <mvcgame/texture/TextureRegion.hpp>

namespace mvcgame {

    void IRenderBridge::beforeDraw()
    {

    }

    void IRenderBridge::afterDraw()
    {
        
    }

    IRenderBridge::Vertices IRenderBridge::getTextureRectVertices(const Texture& texture, const Rect& rect, const TextureRegion& region)
    {
        Rect trect = region / texture;
        Rect rrect = region / rect;
        Vertices vertices = {
            Vertex{
                Point(rrect.origin.x, rrect.origin.y),
                Point(trect.origin.x, trect.origin.y)
            },
            Vertex{
                Point(rrect.origin.x+rrect.size.width, rrect.origin.y),
                Point(trect.origin.x+trect.size.width, trect.origin.y)
            },
            Vertex{
                Point(rrect.origin.x+rrect.size.width, rrect.origin.y+rrect.size.height),
                Point(trect.origin.x+trect.size.width, trect.origin.y+trect.size.height)
            },
            Vertex{
                Point(rrect.origin.x, rrect.origin.y+rrect.size.height),
                Point(trect.origin.x, trect.origin.y+trect.size.height)
            }
        };

        if(region.rotate)
        {
            std::swap(vertices[0].texture, vertices[3].texture);
            std::swap(vertices[0].texture, vertices[1].texture);         
            std::swap(vertices[1].texture, vertices[2].texture);           
        }
        return vertices; 
    }

    void IRenderBridge::drawTexture(std::shared_ptr<const Texture> texture, const Rect& rect, const TextureRegion& region)
    {
        drawTexture(texture, getTextureRectVertices(*texture, rect, region));
    }

    void IRenderBridge::drawTexture(std::shared_ptr<const Texture> texture, const Rect& rect)
    {
        drawTexture(texture, rect, TextureRegion(*texture));
    }
}