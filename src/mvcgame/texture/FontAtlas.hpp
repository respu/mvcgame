

#ifndef mvcgame_FontAtlas_hpp
#define mvcgame_FontAtlas_hpp

#include <mvcgame/texture/TextureAtlas.hpp>

#include <vector>
#include <string>

namespace mvcgame {

    class FontAtlas
    {
    public:
        typedef TextureRegion Region;
        typedef TextureAtlas Page;
        typedef std::vector<Page> Pages;
    private:
        std::string _name;
        unsigned _size;
        bool _bold;
        bool _italic;
        RectBorder _padding;
        Size _spacing;
        float _lineHeight;
        float _baseHeight;
        Scale _scale;
        Pages _pages;
    public:
        FontAtlas();

        const std::string& getName() const;
        void setName(const std::string& name);

        unsigned getSize() const;
        void setSize(unsigned size);

        bool getBold() const;
        void setBold(bool bold);

        bool getItalic() const;
        void setItalic(bool italic);

        const RectBorder& getPadding() const;
        RectBorder& getPadding();

        const Size& getSpacing() const;
        Size& getSpacing();

        float getLineHeight() const;
        void setLineHeight(float h);

        float getBaseHeight() const;
        void setBaseHeight(float h);

        const Scale& getScale() const;
        Scale& getScale();

        const Page& getPage(unsigned i) const;
        Page& getPage(unsigned i);

        const Pages& getPages() const;
        Pages& getPage();
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const FontAtlas& t);
}

#endif