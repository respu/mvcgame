

#ifndef mvcgame_SpriteSheet_hpp
#define mvcgame_SpriteSheet_hpp

#include <mvcgame/texture/SpriteFrame.hpp>

#include <memory>
#include <vector>

namespace mvcgame {

    class Size;
    class TextureAtlas;

    class SpriteSheet
    {
    public:
        typedef std::vector<TextureRegion> TextureRegions;
        typedef SpriteFrame Frame;
        typedef std::vector<Frame> Frames;
    private:
        Frames _frames;
    public:
        SpriteSheet();
        SpriteSheet(std::shared_ptr<Texture> texture);
        SpriteSheet(const Frame& frame);
        SpriteSheet(std::shared_ptr<Texture> texture, const TextureRegions& regions);
        SpriteSheet(const TextureAtlas& altas);
        SpriteSheet(const TextureAtlas& altas, const std::string& name);

        void setRegions(std::shared_ptr<const Texture> texture, const TextureRegions& regions);

        const Frames& getFrames() const;
        Frames& getFrames();

        const Frame& getFrame(unsigned i) const;
        Frame& getFrame(unsigned i);

        unsigned getLength() const;

        Size getSize() const;
    };
}

#endif