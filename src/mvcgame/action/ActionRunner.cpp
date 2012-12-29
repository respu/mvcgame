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

    RunningAction::RunningAction(IActionPtr paction, const Time& pstart, const Duration& pduration) :
    action(std::move(paction)), start(pstart), duration(pduration) 
    {
    }

    RunningAction::~RunningAction()
    {
    }

	ActionRunner::ActionRunner()
	{
	}

	ActionRunner::~ActionRunner()
	{
	}

    void ActionRunner::add(IActionPtr action)
    {
        add(std::move(action), Duration());
    }
    
    void ActionRunner::add(IActionPtr action, const Duration& duration)
    {
        _actions.push_back(RunningActionPtr(new RunningAction(std::move(action), Time(), duration)));
    }

    void ActionRunner::remove(const IAction& action)
    {
        std::remove_if(_actions.begin(), _actions.end(), [&action](const RunningActionPtr& running)
        {
            return running->action.get() == &action;
        });
    }

    void ActionRunner::clear()
    {
        _actions.clear();
    }

    void ActionRunner::update(IView& view, UpdateEvent& event)
    {
        for(RunningActionPtr& running : _actions)
        {
            if(!running->start)
            {
                running->start = event.getTime();
            }
            Duration passed = event.getTime() - Time(running->start);
            float proportion = 1.0f;
            if(running->duration)
            {
                proportion = passed/running->duration;
            }
            running->action->update(view, proportion);
            if(proportion >= 1.0f)
            {
                // mark all finished actions with duration 0
                running->duration = Duration();
            }
        }

        // remove all actions with duration 0
        std::remove_if(_actions.begin(), _actions.end(), [](const RunningActionPtr& running)
        {
            return !running->duration;
        });
    }

}