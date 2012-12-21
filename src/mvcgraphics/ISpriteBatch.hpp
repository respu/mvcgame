//
//  ISpriteBatch.hpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef hydra_ISpriteBatch_hpp
#define hydra_ISpriteBatch_hpp

#include <mvcgraphics/IView.hpp>

namespace mvcgraphics {

    class ISpriteBatch : public IView
    {
    public:
        void addChild(IView* view)
        {
            assert(false) && "A sprite batch only accepts sprites as children, use addSprite.";
        }
        
        virtual void addSprite(ISprite* sprite) = 0;
    };
}

#endif
