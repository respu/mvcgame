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
#include <mvcgame/action/IAction.hpp>

#include <vector>
#include <memory>

namespace mvcgame {

    class View;
    class UpdateEvent;
    class RunningAction;
    typedef std::unique_ptr<RunningAction> RunningActionPtr;        

    /**
     * Represents a running action
     */
    class RunningAction final
    {
    public:
        std::unique_ptr<IAction> action;
        Time start;
        Duration duration;

        RunningAction(std::unique_ptr<IAction> paction, const Time& pstart, const Duration& pduration);
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
        
        void add(std::unique_ptr<IAction> action);
        void add(std::unique_ptr<IAction> action, const Duration& duration);
        
        void remove(const IAction& action);

        void update(View& view, UpdateEvent& event);
    };    
}

#endif