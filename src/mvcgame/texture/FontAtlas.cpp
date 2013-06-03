
#include <mvcgame/texture/FontAtlas.hpp>

namespace mvcgame {

    FontAtlas::FontAtlas() :
    _size(0), _bold(false), _italic(false),
    _lineHeight(0), _baseHeight(0)
    {
    }

    const std::string& FontAtlas::getName() const
    {
        return _name;
    }

    void FontAtlas::setName(const std::string& name)
    {
        _name = name;
    }

    unsigned FontAtlas::getSize() const
    {
        return _size;
    }

    void FontAtlas::setSize(unsigned size)
    {
        _size = size;
    }

    bool FontAtlas::getBold() const
    {
        return _bold;
    }

    void FontAtlas::setBold(bool bold)
    {
        _bold = bold;
    }

    bool FontAtlas::getItalic() const
    {
        return _italic;
    }

    void FontAtlas::setItalic(bool italic)
    {
        _italic = italic;
    }

    const RectBorder& FontAtlas::getPadding() const
    {
        return _padding;
    }

    RectBorder& FontAtlas::getPadding()
    {
        return _padding;
    }

    const Size& FontAtlas::getSpacing() const
    {
        return _spacing;
    }

    Size& FontAtlas::getSpacing()
    {
        return _spacing;
    }

    float FontAtlas::getLineHeight() const
    {
        return _lineHeight;
    }

    void FontAtlas::setLineHeight(float h)
    {
        _lineHeight = h;
    }

    float FontAtlas::getBaseHeight() const
    {
        return _baseHeight;
    }

    void FontAtlas::setBaseHeight(float h)
    {
        _baseHeight = h;
    }

    const Scale& FontAtlas::getScale() const
    {
        return _scale;
    }

    Scale& FontAtlas::getScale()
    {
        return _scale;
    }

    const FontAtlas::Page& FontAtlas::getPage(unsigned i) const
    {
        return _pages.at(i);
    }

    FontAtlas::Page& FontAtlas::getPage(unsigned i)
    {
        if(_pages.size()<=i)
        {
            _pages.resize(i+1);
        }        
        return _pages[i];
    }

    const FontAtlas::Pages& FontAtlas::getPages() const
    {
        return _pages;
    }

    FontAtlas::Pages& FontAtlas::getPage()
    {
        return _pages;
    }

    std::ostream& operator<<(std::ostream& os, const FontAtlas& f)
    {
        os << "FontAtlas( " << f.getName() << std::endl;
        os << "size " << f.getSize() << std::endl;
        if(f.getBold())
        {
            os << " bold" << std::endl;
        }
        if(f.getItalic())
        {
            os << " italic" << std::endl;
        }        
        os << "padding " << f.getPadding() << std::endl;
        os << "spacing " << f.getSpacing() << std::endl;
        os << "scale " << f.getScale() << std::endl;
        os << "height " << f.getLineHeight() << ":" << f.getBaseHeight() << std::endl;
        for(const FontAtlas::Page& page : f.getPages())
        {
            os << page << std::endl;
        }
        os << ")";
        return os;
    }

}