
#ifndef mvcgame_IAction_hpp
#define mvcgame_IAction_hpp

namespace mvcgame {

    class View;

    /**
     * Represents an action over a view.
     * For example an animation.
     */
    class IAction
    {
    public:
        virtual ~IAction(){}
        virtual void update(View& view, float proportion) = 0;

    };
}

#endif
