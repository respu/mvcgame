
#ifndef mvcgame_TileSet_hpp
#define mvcgame_TileSet_hpp

#include <mvcgame/base/Color.hpp>
#include <iostream>

namespace mvcgame {


    class TileSet
    {
    private:
        std::string _name;
        unsigned _tileWidth;
        unsigned _tileHeight;
        unsigned _spacing;
        unsigned _margin;

    public:
        /**
         * Constructor
         */
        TileSet();

        /**
         * The name of this tileset.
         */
        const std::string& getName() const;
        void setName(const std::string& name);
        /**
         * Returns the horizontal size in pixels of a tile
         */
        unsigned getTileWidth() const;
        void setTileWidth(unsigned w);

        /**
         * Returns the vertical size in pixels of a tile
         */ 
        unsigned getTileHeight() const;
        void setTileHeight(unsigned h);

        /**
         * The spacing in pixels between the tiles in this tileset (applies to the tileset image).
         */
        unsigned getSpacing() const;
        void setSpacing(unsigned spacing);

        /**
         * The margin around the tiles in this tileset (applies to the tileset image).
         */
        unsigned getMargin() const;
        void setMargin(unsigned margin);

    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const TileSet& s);    
}

#endif