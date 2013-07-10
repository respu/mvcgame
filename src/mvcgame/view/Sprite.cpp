
#include <mvcgame/view/Sprite.hpp>
#include <mvcgame/platform/IRenderBridge.hpp>

namespace mvcgame {

    Sprite::Sprite() :
    _paused(false), _spriteFrame(0),
    _spriteFrameDuration(1), _spriteFrameUpdates(0)
    {
    }

    Sprite::Sprite(const Sheet& sheet) :
    _paused(false), _spriteFrame(0),
    _spriteFrameDuration(1), _spriteFrameUpdates(0)    
    {
        setSheet(sheet);
    }

    const Sprite::Sheet& Sprite::getSheet() const
    {
        return _sheet;
    }

    void Sprite::setSheet(const Sheet& sheet, bool changeSize)
    {
        _sheet = sheet;
        if(changeSize)
        {
            getFrame().size = _sheet.getSize();
        }
    }

    void Sprite::setSheet(std::shared_ptr<const Texture> texture, bool changeSize)
    {
        setSheet(Sheet(texture), changeSize);
    }

    unsigned Sprite::setSpriteFrame() const
    {
        return _spriteFrame;
    }

    void Sprite::setSpriteFrame(unsigned frame)
    {
        _spriteFrame = frame;
    }

    void Sprite::setSpriteFrameDuration(unsigned num)
    {
        _spriteFrameDuration = num;
    }

    unsigned Sprite::getSpriteFrameDuration() const
    {
        return _spriteFrameDuration;
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
            _spriteFrameUpdates++;
        }
        if(_spriteFrameUpdates >=_spriteFrameDuration)
        {
            _spriteFrame++;
            _spriteFrameUpdates = 0;
        }
        if(_spriteFrame >= _sheet.getLength())
        {
            _spriteFrame = 0;
        }
        View::update();
    }

    void Sprite::draw()
    {
        if(_sheet.getLength()>_spriteFrame)
        {
            const SpriteFrame& frame = _sheet.getFrame(_spriteFrame);
            getBridge().drawTexture(frame.getTexture(), getFrame().size, frame.getRegion());
        }
        View::draw();
    }

}