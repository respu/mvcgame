
#include <mvcgame/view/Sprite.hpp>
#include <mvcgame/platform/IRenderBridge.hpp>

namespace mvcgame {

    Sprite::Sprite() :
    _sheetFrame(0)
    {
    }

    Sprite::Sprite(std::shared_ptr<Sheet> sheet) :
    _sheetFrame(0), _sheet(sheet)
    {
    }

    const Sprite::Sheet& Sprite::getSheet() const
    {
        return *_sheet;
    }

    void Sprite::setSheet(std::shared_ptr<Sheet> sheet)
    {
        _sheet = sheet;
    }

    void Sprite::setSheet(std::shared_ptr<Texture> texture)
    {
        _sheet = std::shared_ptr<Sheet>(new Sheet(texture));
    }

    unsigned Sprite::getSheetFrame() const
    {
        return _sheetFrame;
    }

    void Sprite::setSheetFrame(unsigned frame)
    {
        _sheetFrame = frame;
    }

    void Sprite::setPaused(bool paused)
    {
        _paused = paused;
    }

    bool Sprite::getPaused() const
    {
        return _paused;
    }

    void Sprite::update()
    {
        if(!_paused)
        {
            _sheetFrame++;
        }
        if(_sheetFrame >= _sheet->getLength())
        {
            _sheetFrame = 0;
        }
    }

    void Sprite::draw()
    {
        if(_sheet)
        {
            const SpriteFrame& frame = _sheet->getFrame(_sheetFrame);
            getBridge().drawTexture(getFrame().size, frame.getTexture(), frame.getRegion());
        }
    }

}