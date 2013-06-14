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

#include <cassert>
#include <algorithm>

namespace mvcgame {

    RunningAction::RunningAction(std::unique_ptr<IAction> paction, View& pview, const Duration& pduration) :
    action(std::move(paction)), view(pview), duration(pduration) 
    {
    }

    RunningAction::~RunningAction()
    {
    }

    void RunningAction::update(const UpdateEvent& event)
    {
        if(!start)
        {
            start = event.getTime();
        }
        Duration passed = event.getTime() - start;      
        float proportion = 1.0f;
        if(duration != false)
        {
            proportion = passed/duration;
        }
        action->update(view, proportion);
        if(proportion >= 1.0f)
        {
            // mark all finished actions with duration 0
            duration = Duration();
        }
    }

	ActionRunner::ActionRunner()
	{
	}

	ActionRunner::~ActionRunner()
	{
	}

    void ActionRunner::add(std::unique_ptr<IAction> action, View& view)
    {
        add(std::move(action), view, Duration());
    }
    
    void ActionRunner::add(std::unique_ptr<IAction> action, View& view, const Duration& duration)
    {
        _actions.push_back(std::unique_ptr<RunningAction>(new RunningAction(std::move(action), view, duration)));
    }

    void ActionRunner::remove(View& view)
    {
        _actions.erase(std::remove_if(_actions.begin(), _actions.end(),
        [&view](std::unique_ptr<RunningAction>& running)
        {
            return &running->view == &view;
        }), _actions.end());
    }

    void ActionRunner::remove(const IAction& action)
    {
        _actions.erase(std::remove_if(_actions.begin(), _actions.end(),
        [&action](std::unique_ptr<RunningAction>& running)
        {
            return running->action.get() == &action;
        }), _actions.end());
    }

    void ActionRunner::clear()
    {
        _actions.clear();
    }

    void ActionRunner::update(const UpdateEvent& event)
    {
        for(std::unique_ptr<RunningAction>& running : _actions)
        {
            running->update(event);
        }
        // remove all actions with duration 0
        _actions.erase(std::remove_if(_actions.begin(), _actions.end(),
        [](std::unique_ptr<RunningAction>& running)
        {
            return running->duration == false;
        }), _actions.end());
    }

}