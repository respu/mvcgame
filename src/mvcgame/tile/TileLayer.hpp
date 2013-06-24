
#ifndef mvcgame_TileLayer_hpp
#define mvcgame_TileLayer_hpp

#include <iostream>

namespace mvcgame {


    class TileLayer
    {
    private:
        std::string _name;
        unsigned _width;
        unsigned _height;

    public:
        /**
         * Constructor
         */
        TileLayer();

        /**
         * The name of this layer.
         */
        const std::string& getName() const;
        void setName(const std::string& name);

        /**
         * Returns the horizontal size in pixels
         */
        unsigned getWidth() const;
        void setWidth(unsigned w);

        /**
         * Returns the vertical size in pixels
         */ 
        unsigned getHeight() const;
        void setHeight(unsigned h);

    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const TileLayer& l);    
}

#endif