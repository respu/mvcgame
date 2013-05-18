#include <mvcgame/view/TextureFrame.hpp>
#include <mvcgame/view/ITexture.hpp>

namespace mvcgame {
    
    TextureFrame::TextureFrame(const ITexture& texture) :
    _texture(texture), _frame(Rect(Point(0, 0), texture.getSize()))
    {
    }

    TextureFrame::TextureFrame(const ITexture& texture, const Rect& frame) :
    _texture(texture), _frame(frame)
    {
    }
    
    const ITexture& TextureFrame::getTexture() const
    {
        return _texture;
    }
    
    const Rect& TextureFrame::getFrame() const
    {
        return _frame;
    }

    const Size& TextureFrame::getSize() const
    {
        return _frame.size;
    }
}