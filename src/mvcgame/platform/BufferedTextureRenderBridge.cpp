
#include <mvcgame/platform/BufferedTextureRenderBridge.hpp>

namespace mvcgame {

    BufferedTextureRenderBridge::BufferedTextureRenderBridge(IRenderBridge& innerBridge) :
    _bridge(innerBridge)
    {
    }

    void BufferedTextureRenderBridge::beforeDraw()
    {
        IRenderBridge::beforeDraw();
        _bridge.beforeDraw();
    }

    void BufferedTextureRenderBridge::afterDraw()
    {
        IRenderBridge::afterDraw();
        drawBufferedTexture();
        _bridge.afterDraw();
    }

    void BufferedTextureRenderBridge::loadRootTransform(const Size& size)
    {
        _bridge.loadRootTransform(size);
    }

    void BufferedTextureRenderBridge::pushTransform(const Transform& transform)
    {
        _bridge.pushTransform(transform);
        _bufferedTextureTransform *= transform;
    }

    void BufferedTextureRenderBridge::popTransform(const Transform& transform)
    {
        _bridge.popTransform(transform);
        _bufferedTextureTransform /= transform;
    }

    void BufferedTextureRenderBridge::drawPolygon(const Points& verts, const Color& color)
    {
        drawBufferedTexture();
        _bridge.drawPolygon(verts, color);
    }

    void BufferedTextureRenderBridge::addBufferedTexturePoints(const TexturePoints& points)
    {
        for(const TexturePoint& point : points)
        {
            TexturePoint tpoint(point);
            tpoint.vertex *= _bufferedTextureTransform;
            _bufferedTexturePoints.push_back(tpoint);
        }
    }

    void BufferedTextureRenderBridge::drawTexture(std::shared_ptr<const Texture> texture, const Rect& rect, const TextureRegion& region)
    {
        if(_bufferedTexture != texture)
        {
            drawBufferedTexture();
            _bufferedTexture = texture;
        }
        addBufferedTexturePoints(getTextureRectPoints(*texture, rect, region));
    }

    void BufferedTextureRenderBridge::drawTexture(std::shared_ptr<const Texture> texture, const TexturePoints& points)
    {
        if(_bufferedTexture != texture)
        {
            drawBufferedTexture();
            _bufferedTexture = texture;
        }        
        addBufferedTexturePoints(points);
    }

    void BufferedTextureRenderBridge::drawBufferedTexture()
    {
        if(_bufferedTexture && !_bufferedTexturePoints.empty())
        {
            _bridge.drawTexture(_bufferedTexture, _bufferedTexturePoints);
            _bufferedTexturePoints.clear();
            _bufferedTextureTransform = Transform::Identity;
        }
    }

}