
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
        unsigned _sheetFrame;        
        std::shared_ptr<Sheet> _sheet;
        bool _paused;
    public:
        Sprite();
        Sprite(std::shared_ptr<Sheet> Sheet);

        const Sheet& getSheet() const;
        void setSheet(std::shared_ptr<Sheet> sheet);
        void setSheet(std::shared_ptr<Texture> texture);

        unsigned getSheetFrame() const;
        void setSheetFrame(unsigned frame);

        void setPaused(bool paused);
        bool getPaused() const;

        void update();
        void draw();
    };
    
}


#endif
