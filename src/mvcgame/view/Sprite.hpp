
#ifndef mvcgame_Sprite_hpp
#define mvcgame_Sprite_hpp

#include <mvcgame/view/View.hpp>
#include <mvcgame/texture/SpriteSheet.hpp>
#include <memory>

namespace mvcgame {

    class Sprite : public View
    {
    public:
        typedef SpriteSheet Sheet;
    private:
        bool _paused;        
        unsigned _spriteFrame;
        std::shared_ptr<Sheet> _sheet;        
        unsigned _spriteFrameDuration;
        unsigned _spriteFrameUpdates;
    public:
        Sprite();
        Sprite(std::shared_ptr<Sheet> Sheet);

        const Sheet& getSheet() const;
        void setSheet(std::shared_ptr<Sheet> sheet);
        void setSheet(std::shared_ptr<Texture> texture);

        unsigned setSpriteFrame() const;
        void setSpriteFrame(unsigned frame);

        void setPaused(bool paused);
        bool getPaused() const;

        /**
         * the amount of updated needed to change frame
         */
        void setSpriteFrameDuration(unsigned num);
        unsigned getSpriteFrameDuration() const;

        void update();
        void draw();
    };
    
}


#endif
