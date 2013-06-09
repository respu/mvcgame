
#include <mvcgame/font/FontAtlas.hpp>

namespace mvcgame {

    FontAtlas::FontAtlas()
    {
    }

    const FontAtlas::Info& FontAtlas::getInfo() const
    {
        return _info;
    }

    FontAtlas::Info& FontAtlas::getInfo()
    {
        return _info;
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
        os << "FontAtlas( " << f.getInfo() << std::endl;
        for(const FontAtlas::Page& page : f.getPages())
        {
            os << page << std::endl;
        }
        os << ")";
        return os;
    }

}