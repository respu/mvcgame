
#include <mvcgame/font/FontSheet.hpp>
#include <mvcgame/font/FontAtlas.hpp>
#include <mvcgame/texture/SpriteFrame.hpp>

namespace mvcgame {

    FontSheet::FontSheet()
    {
    }

    FontSheet::FontSheet(const FontAtlas& atlas)
    {
        setInfo(atlas.getInfo());
        for(const FontAtlas::Page& page : atlas.getPages())
        {
            for(const FontAtlas::Page::Region& region : page.getRegions())
            {
                setLetter(region.name, FontLetter(page.getTexture(), region));
            }
        }
    }

    const FontSheet::Info& FontSheet::getInfo() const
    {
        return _info;
    }

    FontSheet::Info& FontSheet::getInfo()
    {
        return _info;
    }

    void FontSheet::setInfo(const Info& info)
    {
        _info = info;
    }

    const FontSheet::Letters& FontSheet::getLetters() const
    {
        return _letters;
    }

    FontSheet::Letters& FontSheet::getLetters()
    {
        return _letters;
    }

    bool FontSheet::hasLetter(const std::string& name) const
    {
        return _letters.find(name) != _letters.end();
    }

    const FontSheet::Letter& FontSheet::getLetter(const std::string& name) const
    {
        return _letters.at(name);
    }

    FontSheet::Letter& FontSheet::getLetter(const std::string& name)
    {
        return _letters[name];
    }

    void FontSheet::setLetter(const std::string& name, Letter letter)
    {
        _letters[name] = letter;
    }

    SpriteFrame FontSheet::getSpriteFrame(const Letter& letter) const
    {
        return letter.getSpriteFrame(_info);
    }
}