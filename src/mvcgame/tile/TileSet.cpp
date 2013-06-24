
#include <mvcgame/tile/TileSet.hpp>

namespace mvcgame {


    TileSet::TileSet() :
    _tileWidth(0),
    _tileHeight(0),
    _spacing(0),
    _margin(0)
    {
    }

    const std::string& TileSet::getName() const
    {
        return _name;
    }

    void TileSet::setName(const std::string& name)
    {
        _name = name;
    }

    unsigned TileSet::getTileWidth() const
    {
        return _tileWidth;
    }

    void TileSet::setTileWidth(unsigned w)
    {
        _tileWidth = w;
    }

    unsigned TileSet::getTileHeight() const
    {
        return _tileHeight;
    }

    void TileSet::setTileHeight(unsigned h)
    {
        _tileHeight = h;
    }

    unsigned TileSet::getSpacing() const
    {
        return _spacing;
    }

    void TileSet::setSpacing(unsigned spacing)
    {
        _spacing = spacing;
    }

    unsigned TileSet::getMargin() const
    {
        return _margin;
    }
    
    void TileSet::setMargin(unsigned margin)
    {
        _margin = margin;
    }
    

    std::ostream& operator<<(std::ostream& os, const TileSet& s)
    {
        os << "TileSet(" << s.getTileWidth() << "x" << s.getTileHeight();
        os << ")";
        return os;
    }
}
