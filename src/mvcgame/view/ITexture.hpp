//
//  ITexture.h
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_ITexture_hpp
#define mvcgame_ITexture_hpp

#include <mvcgame/Geometry.hpp>

namespace mvcgame {
    
    /**
     * Represents a texture
     */
    class ITexture
    {
    public:
        virtual ~ITexture(){};
        virtual const Size& getSize() const = 0;
    };
}

#endif
