//
//  EventEmitter.cpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#include <mvcgame/event/EventEmitter.hpp>
#include <mvcgame/event/Events.hpp>
#include <mvcgame/event/IResponder.hpp>
#include <mvcgame/view/IView.hpp>
#include <mvcgame/controller/ViewController.hpp>

namespace mvcgame {

    EventEmitter::EventEmitter(IViewController& root) : _root(root)
    {
    }

    EventEmitter::~EventEmitter()
    {
    }

    void EventEmitter::emitUpdate(UpdateEvent& event, IViewController& controller)
    {
        controller.respondOnUpdate(event);
        if(event.getStopPropagation())
        {
            return;
        }
        controller.getView().respondOnUpdate(event);
        if(event.getStopPropagation())
        {
            return;
        }
        
        IViewController::ChildrenList& children = controller.getChildren();
        IViewController::ChildrenList::iterator itr;
        for(itr=children.begin(); itr!=children.end(); ++itr)
        {
            emitUpdate(event, **itr);
            if(event.getStopPropagation())
            {
                return;
            }
        }
        if(event.getStopPropagation())
        {
            return;
        }
        controller.updateActions(event);
    }

    void EventEmitter::findTouchResponders(const Point& p, TouchEvent& event, IViewController& controller)
    {
        if(controller.respondToTouchPoint(p, event))
        {
            event.addResponder(controller);
        }
        IView& view = controller.getView();
        if(view.respondToTouchPoint(p, event))
        {
            event.addResponder(view);
        }
        
        IViewController::ChildrenList& children = controller.getChildren();
        IViewController::ChildrenList::iterator itr;
        for(itr=children.begin(); itr!=children.end(); ++itr)
        {
            findTouchResponders(p, event, **itr);
        }
    }

    void EventEmitter::findTouchResponders(TouchEvent& event, IViewController& controller)
    {
        TouchEvent::Points::const_iterator itr;
        
        for(itr=event.getPoints().begin(); itr!=event.getPoints().end(); ++itr)
        {
            findTouchResponders(*itr, event, controller);
        }
    }

    void EventEmitter::emitTouchStart(TouchEvent& event, IViewController& controller)
    {
        findTouchResponders(event, _root);
        TouchEvent::Responders& list = event.getResponders();
        TouchEvent::Responders::iterator itr;
        for(itr=list.begin(); itr!=list.end(); ++itr)
        {
            (**itr).respondOnTouchStart(event);
            if(event.getStopPropagation())
            {
                break;
            }
        }
    }
    
    void EventEmitter::emitTouchEnd(EndTouchEvent &event, IViewController &controller)
    {
        TouchEvent::Responders list = event.getStart().getResponders();
        TouchEvent::Responders::iterator itr;
        for(itr=list.begin(); itr!=list.end(); ++itr)
        {
            (**itr).respondOnTouchStart(event);
            if(event.getStopPropagation())
            {
                break;
            }
        }
    }

    void EventEmitter::emitUpdate(UpdateEvent& event)
    {
        emitUpdate(event, _root);
    }

    void EventEmitter::emitTouchStart(TouchEvent& event)
    {
        emitTouchStart(event, _root);
    }
    
    void EventEmitter::emitTouchEnd(EndTouchEvent& event)
    {
        emitTouchEnd(event, _root);
    }
    
}