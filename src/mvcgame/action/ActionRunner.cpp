//
//  ActionRunner.cpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#include <mvcgame/action/ActionRunner.hpp>
#include <mvcgame/action/IAction.hpp>
#include <mvcgame/event/Events.hpp>

#include <assert.h>
#include <algorithm>

namespace mvcgame {

    RunningAction::RunningAction(IAction* paction, const Time& pstart, const Duration& pduration) :
    action(paction), start(pstart), duration(pduration) 
    {
    }

    RunningAction::~RunningAction()
    {
        delete action;
    }

	ActionRunner::ActionRunner()
	{
	}

	ActionRunner::~ActionRunner()
	{
	}

    void ActionRunner::add(IAction* action)
    {
        add(action, Duration());
    }
    
    void ActionRunner::add(IAction* action, const Duration& duration)
    {
        _actions.push_back(RunningAction(action, Time(), duration));
    }

    void ActionRunner::remove(const IAction& action)
    {
        std::remove_if(_actions.begin(), _actions.end(), [&action](const RunningAction& running){
            return running.action == &action;
        });
    }

    void ActionRunner::clear()
    {
        _actions.clear();
    }

    void ActionRunner::update(IView& view, UpdateEvent& event)
    {
        ActionList::iterator itr;
        for(itr=_actions.begin(); itr!=_actions.end(); ++itr)
        {
            RunningAction& running = *itr;
            if(!running.start)
            {
                running.start = event.getTime();
            }
            Duration passed = event.getTime() - Time(running.start);
            float proportion = 1.0f;
            if(running.duration)
            {
                proportion = passed/running.duration;
            }
            running.action->update(view, proportion);
            if(proportion >= 1.0f)
            {
                // mark all finished actions with duration 0
                running.duration = Duration();
            }
        }

        // remove all actions with duration 0
        std::remove_if(_actions.begin(), _actions.end(), [](const RunningAction& running){
            return !running.duration;
        });
    }

}