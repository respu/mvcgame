
#ifndef mvcgame_Sprite_hpp
#define mvcgame_Sprite_hpp

#include <mvcgame/view/View.hpp>
#include <memory>

namespace mvcgame {

    class Texture;
    
    class Sprite : public View
    {
    private:
        std::shared_ptr<const Texture> _texture;
    public:
        Sprite(std::shared_ptr<const Texture> texture);

        const Texture& getTexture() const;
        void setTexture(std::shared_ptr<const Texture> texture);

        void draw();
    };
    
}


#endif
