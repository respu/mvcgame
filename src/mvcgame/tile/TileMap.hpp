
#ifndef mvcgame_TileMap_hpp
#define mvcgame_TileMap_hpp

#include <mvcgame/base/Color.hpp>
#include <mvcgame/tile/TileSet.hpp>
#include <mvcgame/tile/TileLayer.hpp>

#include <iostream>
#include <vector>

namespace mvcgame {

    class SpriteSheet;

    class TileMap
    {
    public:
        typedef TileSet Set;
        typedef TileLayer Layer;
        typedef std::vector<Set> Sets;
        typedef std::vector<Layer> Layers;
    private:

        unsigned int _width;
        unsigned int _height;
        unsigned int _tileWidth;
        unsigned int _tileHeight;
        Color _background;
        Sets _sets;
        Layers _layers;   

    public:

        /**
         * Constructor
         *
         * @param w the amount of horizontal tiles the map has
         * @param h the amount of vertical tiles the map has
         * @param tw the horizontal size in pixels of a tile
         * @param th the vertical size in pixels of a tile
         */
        TileMap(unsigned int w, unsigned int h, unsigned int tw, unsigned int th);

        /**
         * Returns the amount of horizontal tiles the map has
         */
        unsigned int getWidth() const;

        /**
         * Returns the amount of vertical tiles the map has
         */
        unsigned int getHeight() const;

        /**
         * Returns the horizontal size in pixels of a tile
         */
        unsigned int getTileWidth() const;

        /**
         * Returns the vertical size in pixels of a tile
         */        
        unsigned int getTileHeight() const;

        /**
         * Returns the background color
         */
        const Color& getBackground() const;

        /**
         * Sets the background color
         */
        void setBackground(const Color& color);

        /**
         * Returns the list of tile sets
         */
        Sets& getSets();
        const Sets& getSets() const;

        /**
         * Returns the list of tile layers
         */
        Layers& getLayers();
        const Layers& getLayers() const;

        /**
         * Returns a sprite sheet for a tile type
         */
        SpriteSheet getSheetForTypeId(unsigned typeId) const;

    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const TileMap& t);    
}

#endif