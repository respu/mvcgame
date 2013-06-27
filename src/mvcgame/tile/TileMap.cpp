
#include <mvcgame/tile/TileMap.hpp>
#include <mvcgame/texture/SpriteSheet.hpp>

#include <stdexcept>

namespace mvcgame {


    TileMap::TileMap(unsigned int w, unsigned int h, unsigned int tw, unsigned int th) :
    _width(w), _height(h), _tileWidth(tw), _tileHeight(th)
    {
    }

    unsigned int TileMap::getWidth() const
    {
        return _width;
    }

    unsigned int TileMap::getHeight() const
    {
        return _height;
    }

    unsigned int TileMap::getTileWidth() const
    {
        return _tileWidth;
    }
      
    unsigned int TileMap::getTileHeight() const
    {
        return _tileHeight;
    }

    const Color& TileMap::getBackground() const
    {
        return _background;
    }

    void TileMap::setBackground(const Color& color)
    {
        _background = color;
    }

    TileMap::Sets& TileMap::getSets()
    {
        return _sets;
    }

    const TileMap::Sets& TileMap::getSets() const
    {
        return _sets;
    }

    TileMap::Layers& TileMap::getLayers()
    {
        return _layers;
    }

    const TileMap::Layers& TileMap::getLayers() const
    {
        return _layers;
    }

    SpriteSheet TileMap::getSheetForTypeId(unsigned typeId) const
    {
        for(const TileSet& set : _sets)
        {
            if(set.hasTypeId(typeId))
            {
                return set.getSheetForTypeId(typeId);
            }
        }
        throw std::runtime_error("Tile type id could not be found in the sets.");
    }

    std::ostream& operator<<(std::ostream& os, const TileMap& t)
    {
        os << "TileMap(" << t.getWidth() << "x" << t.getHeight();
        os << " tiles " << t.getTileWidth() << "x" << t.getTileHeight() << std::endl;
        for(const TileSet& set : t.getSets())
        {
            os << set << std::endl;
        }
        for(const TileLayer& layer : t.getLayers())
        {
            os << layer << std::endl;
        }        
        os << ")";
        return os;
    }

}