//
//  ITexture.h
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef __hydra__ITexture__
#define __hydra__ITexture__

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
