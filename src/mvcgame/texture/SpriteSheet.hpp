

#ifndef mvcgame_SpriteSheet_hpp
#define mvcgame_SpriteSheet_hpp

#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/texture/TextureRegion.hpp>

#include <memory>
#include <vector>

namespace mvcgame {

    class TextureAtlas;

    class SpriteFrame
    {
    private:
        std::shared_ptr<Texture> _texture;
        TextureRegion _region;

    public:
        SpriteFrame(std::shared_ptr<Texture> texture);
        SpriteFrame(std::shared_ptr<Texture> texture, const TextureRegion& region);

        const Texture& getTexture() const;
        Texture& getTexture();

        const TextureRegion& getRegion() const;
        TextureRegion& getRegion();
    };

    class SpriteSheet
    {
    public:
        typedef std::vector<TextureRegion> TextureRegions;
        typedef SpriteFrame Frame;
        typedef std::vector<Frame> Frames;
    private:
        Frames _frames;
    public:
        SpriteSheet(std::shared_ptr<Texture> texture);
        SpriteSheet(std::shared_ptr<Texture> texture, const TextureRegions& regions);
        SpriteSheet(std::shared_ptr<Texture> texture, const TextureAtlas& altas);
        SpriteSheet(std::shared_ptr<Texture> texture, const TextureAtlas& altas, const std::string& name);

        void setRegions(std::shared_ptr<Texture> texture, const TextureRegions& regions);

        const Frames& getFrames() const;
        Frames& getFrames();

        const Frame& getFrame(unsigned i) const;
        Frame& getFrame(unsigned i);

        unsigned getLength() const;
    };
}

#endif