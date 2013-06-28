

#ifndef mvcgame_SpriteFrame_hpp
#define mvcgame_SpriteFrame_hpp

#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/texture/TextureRegion.hpp>

#include <memory>

namespace mvcgame {

    class SpriteFrame
    {
    private:
        std::shared_ptr<const Texture> _texture;
        TextureRegion _region;

    public:
        SpriteFrame();
        SpriteFrame(std::shared_ptr<const Texture> texture);
        SpriteFrame(std::shared_ptr<const Texture> texture, const TextureRegion& region);

        const Texture& getTexture() const;
        Texture& getTexture();

        const TextureRegion& getRegion() const;
        TextureRegion& getRegion();
    };


    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const SpriteFrame& f);    

}

#endif