#ifndef mvcgame_gl_RenderBridge_hpp
#define mvcgame_gl_RenderBridge_hpp

#include <mvcgame/platform/IRenderBridge.hpp>
#include <map>

namespace mvcgame {

    class RenderBridge : public IRenderBridge
    {
    public:
        typedef std::map<const Texture*, unsigned int> Textures;
    private:
        Textures _textures;
        unsigned int _texture;

        static void getGlTransform(const Transform& t, float* m);
    public:
        RenderBridge();
        void loadRootTransform(const Size& size);
        void pushTransform(const Transform& transform);
        void popTransform(const Transform& transform);        
        void drawPolygon(const Points& verts, const Color& color);
        void loadTexture(const Texture& texture);
        void drawTexture(const Rect& rect, const Texture& texture, const TextureRegion& region);
    };

}

#endif