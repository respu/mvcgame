
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
        if(_bufferedTextureTransforms.empty())
        {
            _bufferedTextureVertices.insert(_bufferedTextureVertices.end(), vertices.begin(), vertices.end());
        }
        else
        {
            for(const Vertex& vertex : vertices)
            {
                Vertex tvertex(vertex);
                tvertex.position *= _bufferedTextureTransforms.top();
                _bufferedTextureVertices.push_back(tvertex);
            }
        }
    }

    void BufferedTextureRenderBridge::drawBufferedTexture()
    {
        if(_bufferedTexture && !_bufferedTextureVertices.empty())
        {
            if(!_bufferedTextureTransforms.empty())
            {
                Transform inverse = _bufferedTextureTransforms.top().invert();
                for(Vertex& vertex : _bufferedTextureVertices)
                {
                    vertex.position *= inverse;
                }
            }
            _bridge.drawTexture(_bufferedTexture, _bufferedTextureVertices);
            _bufferedTextureVertices.clear();
        }
    }

}