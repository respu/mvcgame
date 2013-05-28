#ifndef mvcgame_dx_RenderBridge_hpp
#define mvcgame_dx_RenderBridge_hpp

#include <mvcgame/platform/IRenderBridge.hpp>

namespace mvcgame {

    class RenderBridge : public IRenderBridge
    {
    public:
        void loadRootTransform(const Size& size);
        void pushTransform(const Transform& transform);
        void popTransform(const Transform& transform);        
        void drawPolygon(const Points& verts, const Color& color);
        void loadTexture(const Texture& texture);
        void drawTexture(const Rect& rect, const Texture& texture, const TextureRegion& region);
    };

}

#endif