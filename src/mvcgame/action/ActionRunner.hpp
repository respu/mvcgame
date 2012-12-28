//
//  ActionRunner.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_ActionRunner_hpp
#define mvcgame_ActionRunner_hpp

#include <mvcgame/Time.hpp>

#include <vector>

namespace mvcgame {

    class IAction;
    class IView;
    class UpdateEvent;
    class RunningAction;

    /**
     * Represents a running action
     */
    class RunningAction final
    {
    public:
        IAction* action;
        Time start;
        Duration duration;

        RunningAction(IAction* paction, const Time& pstart, const Duration& pduration);
        ~RunningAction();
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
    public:
        ActionRunner();

        virtual ~ActionRunner();

        void clear();
        
        void add(IAction* action);
        void add(IAction* action, const Duration& duration);
        
        void remove(const IAction& action);

        void update(IView& view, UpdateEvent& event);
    };    
}

#endif