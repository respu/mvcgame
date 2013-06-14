
#ifndef mvcgame_ActionRunner_hpp
#define mvcgame_ActionRunner_hpp

#include <mvcgame/base/Time.hpp>
#include <mvcgame/action/IAction.hpp>

#include <vector>
#include <memory>

namespace mvcgame {

    class View;
    class UpdateEvent;     

    /**
     * Represents a running action
     */
    class RunningAction final
    {
    public:
        std::unique_ptr<IAction> action;
        View& view;
        Time start;
        Duration duration;

        RunningAction(std::unique_ptr<IAction> action, View& view, const Duration& duration);
        ~RunningAction();

        void update(const UpdateEvent& event);
    };

    /**
     * Maintains a list of actions and can update them
     */
    class ActionRunner
    {
    public:
        typedef std::vector<std::unique_ptr<RunningAction>> ActionList;       
    private:
        ActionList _actions;
    public:
        ActionRunner();

        virtual ~ActionRunner();

        void clear();
        
        void add(std::unique_ptr<IAction> action, View& view);
        void add(std::unique_ptr<IAction> action, View& view, const Duration& duration);
        
        void remove(View& view);
        void remove(const IAction& action);

        void update(const UpdateEvent& event);
    };    
}

#endif