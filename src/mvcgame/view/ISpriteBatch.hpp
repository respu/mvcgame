//
//  ISpriteBatch.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_ISpriteBatch_hpp
#define mvcgame_ISpriteBatch_hpp

#include <mvcgame/view/IView.hpp>

namespace mvcgame {

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
