 
 #include <mvcgame/tile/Tile.hpp>   

namespace mvcgame {


    Tile::Tile() :
    _typeId(0), _flip(Flip::None)
    {
    }    

    Tile::Tile(unsigned typeId, Flip flip) :
    _typeId(typeId), _flip(flip)
    {
    }

    unsigned Tile::getTypeId() const
    {
        return _typeId;
    }

    void Tile::setTypeId(unsigned id)
    {
        _typeId = id;
    }

    Tile::Flip Tile::getFlip() const
    {
        return _flip;
    }

    void Tile::setFlip(Flip f)
    {
        _flip = f;
    }

    std::ostream& operator<<(std::ostream& os, const Tile& t)
    {
        os << "Tile(" << t.getTypeId() ;
        switch(t.getFlip())
        {
            case Tile::Flip::Horizontal:
                os << "flip h";
                break;
            case Tile::Flip::Vertical:
                os << "flip v";
                break;
            case Tile::Flip::Diagonal:
                os << "flip d";
                break;
            default:
                break;
        }
        os << ")";
        return os;
    }

}