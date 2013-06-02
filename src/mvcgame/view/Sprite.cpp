
#include <mvcgame/view/Sprite.hpp>
#include <mvcgame/platform/IRenderBridge.hpp>

namespace mvcgame {

    Sprite::Sprite() :
    _paused(false), _spriteFrame(0),
    _spriteFrameDuration(1), _spriteFrameUpdates(0)
    {
    }

    Sprite::Sprite(std::shared_ptr<Sheet> sheet) :
    _paused(false), _spriteFrame(0), _sheet(sheet),
    _spriteFrameDuration(1), _spriteFrameUpdates(0)    
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
        if(_spriteFrame >= _sheet->getLength())
        {
            _spriteFrame = 0;
        }
        View::update();
    }

    void Sprite::draw()
    {
        if(_sheet)
        {
            const SpriteFrame& frame = _sheet->getFrame(_spriteFrame);
            getBridge().drawTexture(getFrame().size, frame.getTexture(), frame.getRegion());
        }
        View::draw();
    }

}