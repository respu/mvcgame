
#ifndef mvcgame_Tile_hpp
#define mvcgame_Tile_hpp

#include <iostream>

namespace mvcgame {

    class Tile
    {
    public:
        enum class Flip
        {
            None,
            Horizontal,
            Vertical,
            Diagonal
        };
    private:
        unsigned _typeId;
        Flip _flip;

    public:
        Tile();
        Tile(unsigned typeId, Flip flip=Flip::None);

        unsigned getTypeId() const;
        void setTypeId(unsigned id);
        Flip getFlip() const;
        void setFlip(Flip f);
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const Tile& t);  
}

#endif