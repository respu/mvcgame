#ifndef mvcgame_gl_RenderBridge_hpp
#define mvcgame_gl_RenderBridge_hpp

#include <mvcgame/platform/IRenderBridge.hpp>
#include <map>

namespace mvcgame {

    class RenderBridge : public IRenderBridge
    {
    public:
        typedef std::map<const Texture*, unsigned int> Textures;
        typedef std::vector<float> FloatList;
    private:
        Textures _textures;
        Transform _transform;
        static void getGlTransform(const Transform& t, float* m);
        void loadTexture(const Texture& texture);
    public:
        RenderBridge();
        void setTransform(const Transform& transform);        
        void drawPolygon(const Points& verts, const Color& color);
        void drawTexture(std::shared_ptr<const Texture> texture, const Vertices& vertices);
        void drawTexture(std::shared_ptr<const Texture> texture, const Rect& rect, const TextureRegion& region);
    };

}

#endif