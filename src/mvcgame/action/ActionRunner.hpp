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
#include <memory>

namespace mvcgame {

    class IAction;
    class IView;
    class UpdateEvent;
    class RunningAction;
    typedef std::unique_ptr<IAction> IActionPtr;
    typedef std::unique_ptr<RunningAction> RunningActionPtr;        

    /**
     * Represents a running action
     */
    class RunningAction final
    {
    public:
        IActionPtr action;
        Time start;
        Duration duration;

        RunningAction(IActionPtr paction, const Time& pstart, const Duration& pduration);
        ~RunningAction();
    };

    /**
     * Maintains a list of actions and can update them
     */
    class ActionRunner
    {
    public:
        typedef std::vector<RunningActionPtr> ActionList;       
    private:
        ActionList _actions;
    public:
        ActionRunner();

        virtual ~ActionRunner();

        void clear();
        
        void add(IActionPtr action);
        void add(IActionPtr action, const Duration& duration);
        
        void remove(const IAction& action);

        void update(IView& view, UpdateEvent& event);
    };    
}

#endif