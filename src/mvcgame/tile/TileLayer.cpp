
#include <mvcgame/tile/TileLayer.hpp>

namespace mvcgame {


    TileLayer::TileLayer() :
    _width(0),
    _height(0)
    {
    }

    const std::string& TileLayer::getName() const
    {
        return _name;
    }

    void TileLayer::setName(const std::string& name)
    {
        _name = name;
    }

    unsigned TileLayer::getWidth() const
    {
        return _width;
    }

    void TileLayer::setWidth(unsigned w)
    {
        _width = w;
        _tiles.resize(w);
    }

    unsigned TileLayer::getHeight() const
    {
        return _height;
    }

    void TileLayer::setHeight(unsigned h)
    {
        _height = h;
        for(Tiles& row : _tiles)
        {
            row.resize(h);
        }
    }

    Tile& TileLayer::getTile(unsigned x, unsigned y)
    {
        return _tiles[x][y];
    }

    const Tile& TileLayer::getTile(unsigned x, unsigned y) const
    {
        return _tiles.at(x).at(y);
    }

    void TileLayer::setTile(unsigned x, unsigned y, const Tile& tile)
    {
        _tiles[x][y] = tile;
    }

    std::ostream& operator<<(std::ostream& os, const TileLayer& l)
    {
        os << "TileLayer(" << l.getWidth() << "x" << l.getHeight() << std::endl;
        for (unsigned y = 0; y < l.getHeight(); ++y)
        {
            os << "[";
            for (unsigned x = 0; x < l.getWidth(); ++x)
            {
                const Tile& t = l.getTile(x, y);
                os << t.getTypeId();
                if(x < l.getWidth() - 1)
                {
                    os << ", ";
                }
            }
            os << "]" << std::endl;
        }
        os << ")";
        return os;
    }
}
