
#include <mvcgame/event/EventEmitter.hpp>
#include <mvcgame/event/Events.hpp>
#include <mvcgame/controller/BaseViewController.hpp>
#include <mvcgame/controller/ViewController.hpp>

namespace mvcgame {

    EventEmitter::EventEmitter(BaseViewController& root) : _root(root)
    {
    }

    EventEmitter::~EventEmitter()
    {
    }

    void EventEmitter::emitUpdate(UpdateEvent& event, BaseViewController& controller)
    {
        controller.respondOnUpdate(event);
        if(event.getStopPropagation())
        {
            return;
        }

        const BaseViewController::Children& children = controller.getChildren();
        BaseViewController::Children::const_iterator itr;
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
    }

    void EventEmitter::findTouchResponders(const Point& p, TouchEvent& event, BaseViewController& controller)
    {
        if(controller.respondToTouchPoint(p, event))
        {
            event.addResponder(controller);
        }
        
        const BaseViewController::Children& children = controller.getChildren();
        BaseViewController::Children::const_iterator itr;
        for(itr=children.begin(); itr!=children.end(); ++itr)
        {
            findTouchResponders(p, event, **itr);
        }
    }

    void EventEmitter::findTouchResponders(TouchEvent& event, BaseViewController& controller)
    {
        TouchEvent::Points::const_iterator itr;
        
        for(itr=event.getPoints().begin(); itr!=event.getPoints().end(); ++itr)
        {
            findTouchResponders(*itr, event, controller);
        }
    }

    void EventEmitter::emitTouchStart(TouchEvent& event, BaseViewController& controller)
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
    
    void EventEmitter::emitTouchEnd(EndTouchEvent &event, BaseViewController &controller)
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