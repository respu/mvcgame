
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

    void BufferedTextureRenderBridge::setTransform(const Transform& transform)
    {
        _bridge.setTransform(transform);
        _transform = transform;
    }

    void BufferedTextureRenderBridge::drawPolygon(const Points& verts, const Color& color)
    {
        drawBufferedTexture();
        _bridge.drawPolygon(verts, color);
    }

    void BufferedTextureRenderBridge::drawTexture(std::shared_ptr<const Texture> texture, const Rect& rect, const TextureRegion& region)
    {
        startBufferedTexture(texture);
        addBufferedTextureVertices(getTextureRectVertices(*texture, rect, region));
    }

    void BufferedTextureRenderBridge::drawTexture(std::shared_ptr<const Texture> texture, const Vertices& vertices)
    {
        startBufferedTexture(texture);
        addBufferedTextureVertices(vertices);
    }

    void BufferedTextureRenderBridge::startBufferedTexture(std::shared_ptr<const Texture> texture)
    {
        if(_bufferedTexture != texture)
        {
            drawBufferedTexture();
            _bufferedTexture = texture;
        }
    }

    void BufferedTextureRenderBridge::addBufferedTextureVertices(const Vertices& vertices)
    {
        for(const Vertex& vertex : vertices)
        {
            Vertex tvertex(vertex);
            tvertex.position *= _transform;
            _bufferedTextureVertices.push_back(tvertex);
        }
    }

    void BufferedTextureRenderBridge::drawBufferedTexture()
    {
        if(_bufferedTexture && !_bufferedTextureVertices.empty())
        {
            Transform inverse = _transform.invert();
            for(Vertex& vertex : _bufferedTextureVertices)
            {
                vertex.position *= inverse;
            }
            _bridge.drawTexture(_bufferedTexture, _bufferedTextureVertices);
            _bufferedTextureVertices.clear();
        }
    }

}