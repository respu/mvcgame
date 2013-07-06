
#include <mvcgame/platform/BufferedTextureRenderBridge.hpp>

namespace mvcgame {

    BufferedTextureRenderBridge::BufferedTextureRenderBridge(IRenderBridge& innerBridge) :
    _bridge(innerBridge)
    {
    }

    void BufferedTextureRenderBridge::beforeDraw()
    {
        IRenderBridge::beforeDraw();
        _bufferedTextureTransforms = TransformStack();
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
        if(_bufferedTextureTransforms.empty())
        {
            _bufferedTextureTransforms.push(transform);
        }
        else
        {
            _bufferedTextureTransforms.push(_bufferedTextureTransforms.top()*transform);
        }
    }

    void BufferedTextureRenderBridge::popTransform(const Transform& transform)
    {
        _bridge.popTransform(transform);
        _bufferedTextureTransforms.pop();
    }

    void BufferedTextureRenderBridge::drawPolygon(const Points& verts, const Color& color)
    {
        drawBufferedTexture();
        _bridge.drawPolygon(verts, color);
    }

    void BufferedTextureRenderBridge::drawTexture(std::shared_ptr<const Texture> texture, const Rect& rect, const TextureRegion& region)
    {
        startBufferedTexture(texture);
        addBufferedTexturePoints(getTextureRectPoints(*texture, rect, region));
    }

    void BufferedTextureRenderBridge::drawTexture(std::shared_ptr<const Texture> texture, const TexturePoints& points)
    {

        startBufferedTexture(texture);
        addBufferedTexturePoints(points);
    }

    void BufferedTextureRenderBridge::startBufferedTexture(std::shared_ptr<const Texture> texture)
    {
        if(_bufferedTexture != texture)
        {
            drawBufferedTexture();
            _bufferedTexture = texture;
        }
    }

    void BufferedTextureRenderBridge::addBufferedTexturePoints(const TexturePoints& points)
    {
        if(_bufferedTextureTransforms.empty())
        {
            _bufferedTexturePoints.insert(_bufferedTexturePoints.end(), points.begin(), points.end());
        }
        else
        {
            for(const TexturePoint& point : points)
            {
                TexturePoint tpoint(point);
                tpoint.vertex *= _bufferedTextureTransforms.top();
                _bufferedTexturePoints.push_back(tpoint);
            }
        }
    }

    void BufferedTextureRenderBridge::drawBufferedTexture()
    {
        if(_bufferedTexture && !_bufferedTexturePoints.empty())
        {
            if(!_bufferedTextureTransforms.empty())
            {
                Transform inverse = _bufferedTextureTransforms.top().invert();
                for(TexturePoint& point : _bufferedTexturePoints)
                {
                    point.vertex *= inverse;
                }
            }
            _bridge.drawTexture(_bufferedTexture, _bufferedTexturePoints);
            _bufferedTexturePoints.clear();
        }
    }

}