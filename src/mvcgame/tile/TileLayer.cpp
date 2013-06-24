
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
    }

    unsigned TileLayer::getHeight() const
    {
        return _height;
    }

    void TileLayer::setHeight(unsigned h)
    {
        _height = h;
    }

    std::ostream& operator<<(std::ostream& os, const TileLayer& l)
    {
        os << "TileLayer(" << l.getWidth() << "x" << l.getHeight();
        os << ")";
        return os;
    }
}
