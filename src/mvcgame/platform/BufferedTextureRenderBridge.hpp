#ifndef mvcgame_BufferedTextureRenderBridge_hpp
#define mvcgame_BufferedTextureRenderBridge_hpp

#include <mvcgame/platform/IRenderBridge.hpp>

namespace mvcgame {

    class BufferedTextureRenderBridge : public IRenderBridge
    {
    private:
        IRenderBridge& _bridge;
        std::shared_ptr<const Texture> _bufferedTexture;
        TexturePoints _bufferedTexturePoints;
        Transform _bufferedTextureTransform;

        void drawBufferedTexture();
        void addBufferedTexturePoints(const TexturePoints& points);
    public:
        BufferedTextureRenderBridge(IRenderBridge& innerBridge);
        void beforeDraw();
        void afterDraw();
        void loadRootTransform(const Size& size);
        void pushTransform(const Transform& transform);
        void popTransform(const Transform& transform);        
        void drawPolygon(const Points& verts, const Color& color);
        void drawTexture(std::shared_ptr<const Texture> texture, const Rect& rect, const TextureRegion& region);
        void drawTexture(std::shared_ptr<const Texture> texture, const TexturePoints& points);
    };

}

#endif