//
//  ActionRunner.hpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef hydra_ActionRunner_hpp
#define hydra_ActionRunner_hpp

#include <mvcgraphics/Time.hpp>
#include <mvcgraphics/IAction.hpp>
#include <vector>

namespace mvcgraphics {

    class IView;
    class UpdateEvent;

    /**
     * Represents a running action
     */
    struct RunningAction
    {
        IAction* action;
        Time start;
        Duration duration;

        RunningAction(IAction* paction, const Time& pstart, const Duration& pduration) :
        action(paction), start(pstart), duration(pduration) 
        {
        }

        ~RunningAction()
        {
            delete action;
        }
    };

    /**
     * Maintains a list of actions and can update them
     */
    class ActionRunner
    {
    public:
        typedef std::vector<RunningAction> ActionList;
    private:
        ActionList _actions;
    protected:
        void setView(IView* view);
    public:
        ActionRunner();

        virtual ~ActionRunner();

        void clear();
        
        void add(IAction* action);
        void add(IAction* action, const Duration& duration);
        
        void remove(IAction* action);

        void update(IView& view, UpdateEvent& event);
    };    
}


#endif