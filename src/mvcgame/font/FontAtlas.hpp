  
#ifndef mvcgame_FontAtlas_hpp
#define mvcgame_FontAtlas_hpp

#include <mvcgame/font/FontInfo.hpp>
#include <mvcgame/font/FontAtlasPage.hpp>
#include <vector>
#include <memory>

namespace mvcgame {

    class FontAtlas : public std::enable_shared_from_this<FontAtlas>
    {
    public:
        typedef FontInfo Info;
        typedef FontAtlasPage Page;
        typedef std::vector<Page> Pages;
    private:
        Info _info;
        Pages _pages;
    public:
        FontAtlas();

        const Info& getInfo() const;
        Info& getInfo();
    
        const Page& getPage(unsigned i) const;
        Page& getPage(unsigned i);

        const Pages& getPages() const;
        Pages& getPage();
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const FontAtlas& i);
}

#endif