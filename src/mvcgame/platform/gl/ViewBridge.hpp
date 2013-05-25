#ifndef mvcgame_gl_ViewBridge_hpp
#define mvcgame_gl_ViewBridge_hpp

#include <mvcgame/platform/IViewBridge.hpp>

namespace mvcgame {

    class ViewBridge : public IViewBridge
    {
    public:
        void loadRootTransform(const Size& size);
        void pushTransform(const Transform& transform);
        void popTransform(const Transform& transform);        
        void drawPolygon(const Points& verts, const Color& color);
        void loadTexture(const Texture& texture);
        void drawTexture(const Rect& rect, const Texture& texture, const Rect& textureRect);
    };

}

#endif