
#include <mvcgame/texture/SpriteSheet.hpp>
#include <mvcgame/texture/TextureAtlas.hpp>

#include <algorithm>

namespace mvcgame {

    SpriteSheet::SpriteSheet()
    {
    }    

    SpriteSheet::SpriteSheet(std::shared_ptr<const Texture> texture)
    {
        _frames.push_back(Frame(texture));
    }

    SpriteSheet::SpriteSheet(const Frame& frame)
    {
        _frames.push_back(frame);
    }

    SpriteSheet::SpriteSheet(std::shared_ptr<const Texture> texture, const TextureRegion& region)
    {
        TextureRegions regions;
        regions.push_back(region);
        setRegions(texture, regions);
    }

    SpriteSheet::SpriteSheet(std::shared_ptr<const Texture> texture, const TextureRegions& regions)
    {
        setRegions(texture, regions);
    }

    SpriteSheet::SpriteSheet(const TextureAtlas& atlas)
    {
        TextureRegions regions(atlas.getRegions());
        std::sort(regions.begin(), regions.end());
        setRegions(atlas.getTexture(), regions);
    }

    SpriteSheet::SpriteSheet(const TextureAtlas& atlas, const std::string& name)
    {
        TextureRegions regions(atlas.getRegions(name));
        std::sort(regions.begin(), regions.end());
        setRegions(atlas.getTexture(), regions);
    }

    void SpriteSheet::setRegions(std::shared_ptr<const Texture> texture, const TextureRegions& regions)
    {
        for(const TextureRegion& region : regions)
        {
            _frames.push_back(Frame(texture, region));
        }
    }

    const SpriteSheet::Frames& SpriteSheet::getFrames() const
    {
        return _frames;
    }

    SpriteSheet::Frames& SpriteSheet::getFrames()
    {
        return _frames;
    }

    const SpriteSheet::Frame& SpriteSheet::getFrame(unsigned i) const
    {
        return _frames.at(i);
    }

    SpriteSheet::Frame& SpriteSheet::getFrame(unsigned i)
    {
        return _frames.at(i);
    }

    unsigned SpriteSheet::getLength() const
    {
        return _frames.size();
    }

    Size SpriteSheet::getSize() const
    {
        Size size;
        for(const Frame& frame : _frames)
        {
            gunit_t w = frame.getRegion().originalWidth;
            gunit_t h = frame.getRegion().originalHeight;
            size.width = std::max(w, size.width);
            size.height = std::max(h, size.height);
        }
        return size;
    }
}