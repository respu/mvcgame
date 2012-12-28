//
//  ISprite.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_ISprite_hpp
#define mvcgame_ISprite_hpp

#include <mvcgame/view/IView.hpp>

namespace mvcgame {

    class ITexture;
    
    class ISprite : public IView
    {
    public:
        const ITexture& getTexture() const;
        
        /**
         * The texture should not be deleted
         * as many sprites can use the same one
         */
        void setTexture(const ITexture& texture);

        const Anchor& getAnchor() const;

        void setAnchor(const Anchor& anchor);
    };
    
}


#endif
