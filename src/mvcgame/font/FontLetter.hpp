

#ifndef mvcgame_FontLetter_hpp
#define mvcgame_FontLetter_hpp

#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/font/FontRegion.hpp>

#include <memory>

namespace mvcgame {

    class SpriteFrame;
    class FontInfo;

    class FontLetter
    {
    private:
        std::shared_ptr<Texture> _texture;
        FontRegion _region;

    public:
        FontLetter();
        FontLetter(std::shared_ptr<Texture> texture);
        FontLetter(std::shared_ptr<Texture> texture, const FontRegion& region);

        const Texture& getTexture() const;
        Texture& getTexture();

        const FontRegion& getRegion() const;
        FontRegion& getRegion();

        SpriteFrame getSpriteFrame(const FontInfo& info) const;
    };


    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const FontLetter& f);    

}

#endif