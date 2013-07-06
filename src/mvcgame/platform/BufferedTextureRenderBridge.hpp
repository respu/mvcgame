#ifndef mvcgame_BufferedTextureRenderBridge_hpp
#define mvcgame_BufferedTextureRenderBridge_hpp

#include <mvcgame/platform/IRenderBridge.hpp>

#include <stack>

namespace mvcgame {

    class BufferedTextureRenderBridge : public IRenderBridge
    {
    private:
        typedef std::stack<Transform> TransformStack;
        IRenderBridge& _bridge;
        std::shared_ptr<const Texture> _bufferedTexture;
        TexturePoints _bufferedTexturePoints;
        TransformStack _bufferedTextureTransforms;

        void startBufferedTexture(std::shared_ptr<const Texture> texture);
        void drawBufferedTexture();
        void clearBufferedTexture();
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