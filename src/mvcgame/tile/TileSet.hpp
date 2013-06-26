
#ifndef mvcgame_TileSet_hpp
#define mvcgame_TileSet_hpp

#include <mvcgame/base/Color.hpp>
#include <mvcgame/texture/Texture.hpp>

#include <iostream>
#include <memory>

namespace mvcgame {

    class TextureRegion;

    class TileSet
    {
    private:
        std::string _name;
        unsigned _tileWidth;
        unsigned _tileHeight;
        unsigned _spacing;
        unsigned _margin;
        unsigned _firstTypeId;
        unsigned _offsetX;
        unsigned _offsetY;
        std::shared_ptr<const Texture> _texture;

    public:
        /**
         * Constructor
         */
        TileSet();

        /**
         * The texture of this tileset.
         */
        std::shared_ptr<const Texture> getTexture() const;
        void setTexture(std::shared_ptr<const Texture> texture);

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
         * Returns horizontal offset in pixels
         */
        unsigned getTileOffsetX() const;
        void setTileOffsetX(unsigned x);

        /**
         * Returns vertical offset in pixels (positive is down)
         */ 
        unsigned getTileOffsetY() const;
        void setTileOffsetY(unsigned y);        

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

        /**
         * The id if the first (top left) tile type. Then it goes from left to right
         * and from top to bottom
         */
        unsigned getFirstTypeId() const;
        void setFirstTypeId(unsigned typeId);

        /**
         * Returns a texture region for a tile type
         */
        TextureRegion getRegionForTypeId(unsigned typeId);
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const TileSet& s);    
}

#endif