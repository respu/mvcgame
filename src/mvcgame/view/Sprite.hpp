
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
        Sheet _sheet;        
        unsigned _spriteFrameDuration;
        unsigned _spriteFrameUpdates;
    public:
        Sprite();
        Sprite(const Sheet& sheet);
        Sprite(std::shared_ptr<const TextureAtlas> atlas);
        Sprite(const TextureAtlas& atlas);
        Sprite(std::shared_ptr<const Texture> texture);

        const Sheet& getSheet() const;
        void setSheet(const Sheet& sheet, bool changeSize=true);
        void setSheet(std::shared_ptr<const Texture> texture, bool changeSize=true);

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
