//
//  IAction.hpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef hydra_IAction_hpp
#define hydra_IAction_hpp

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
