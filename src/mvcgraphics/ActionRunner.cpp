//
//  ActionRunner.cpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#include <mvcgraphics/ActionRunner.hpp>
#include <mvcgraphics/Events.hpp>
#include <assert.h>

namespace mvcgraphics {

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
        // cannot add the same action twice
        assert(std::find_if(_actions.begin(), _actions.end(), [action](const RunningAction& running){
            return running.action == action;
        }) == _actions.end());
        _actions.push_back(RunningAction(action, Time(), duration));
    }

    void ActionRunner::remove(IAction* action)
    {
      std::remove_if(_actions.begin(), _actions.end(), [action](const RunningAction& running){
            return running.action == action;
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
            if(!itr->start)
            {
                itr->start = event.getTime();
            }
            Duration passed = event.getTime() - Time(itr->start);
            float proportion = 1.0f;
            if(itr->duration)
            {
                proportion = passed/itr->duration;
            }
            itr->action->update(view, proportion);
            if(proportion >= 1.0f)
            {
                // mark all finished actions with duration 0
                itr->duration = Duration();
            }
        }

        // remove all actions with duration 0
        std::remove_if(_actions.begin(), _actions.end(), [](const RunningAction& running){
            return !running.duration;
        });
    }

}