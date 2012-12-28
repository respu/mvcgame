//
//  IAction.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_IAction_hpp
#define mvcgame_IAction_hpp

#include <mvcgame/Time.hpp>
#include <mvcgame/IView.hpp>

namespace mvcgame {
    
    class IView;

    /**
     * Represents an action over a view.
     * For example an animation.
     */
    class IAction
    {
    public:
        virtual ~IAction(){}
        virtual void update(IView& view, float proportion) = 0;

    };
}


#endif
