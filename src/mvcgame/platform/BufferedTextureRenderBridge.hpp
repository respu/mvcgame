#ifndef mvcgame_BufferedTextureRenderBridge_hpp
#define mvcgame_BufferedTextureRenderBridge_hpp

#include <mvcgame/platform/IRenderBridge.hpp>

#include <stack>

namespace mvcgame {

    class BufferedTextureRenderBridge : public IRenderBridge
    {
    private:
        IRenderBridge& _bridge;
        std::shared_ptr<const Texture> _bufferedTexture;
        Vertices _bufferedTextureVertices;
        Transform _transform;

        void startBufferedTexture(std::shared_ptr<const Texture> texture);
        void drawBufferedTexture();
        void clearBufferedTexture();
        void addBufferedTextureVertices(const Vertices& vertices);
    public:
        BufferedTextureRenderBridge(IRenderBridge& innerBridge);
        void beforeDraw();
        void afterDraw();
        void setTransform(const Transform& transform);
        void drawPolygon(const Points& verts, const Color& color);
        void drawTexture(std::shared_ptr<const Texture> texture, const Rect& rect, const TextureRegion& region);
        void drawTexture(std::shared_ptr<const Texture> texture, const Vertices& vertices);
    };

}

#endif