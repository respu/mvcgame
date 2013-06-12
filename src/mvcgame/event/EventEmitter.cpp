
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
#ifdef MVCGAME_DEBUG_EVENTS
        std::cout << ">>>>" << std::endl;        
        std::cout << "EventEmitter::emitTouchStart " << std::endl;
        std::cout << event << std::endl;
        std::cout << "<<<<" << std::endl;
#endif

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

void EventEmitter::emitTouchUpdate(UpdateTouchEvent &event, BaseViewController &controller)
    {
#ifdef MVCGAME_DEBUG_EVENTS
        std::cout << ">>>>" << std::endl;        
        std::cout << "EventEmitter::emitTouchUpdate " << std::endl;
        std::cout << event << std::endl;
        std::cout << "<<<<" << std::endl;
#endif

        TouchEvent::Responders list = event.getStart().getResponders();
        TouchEvent::Responders::iterator itr;
        for(itr=list.begin(); itr!=list.end(); ++itr)
        {
            (**itr).respondOnTouchUpdate(event);
            if(event.getStopPropagation())
            {
                break;
            }
        }
    }    
    
    void EventEmitter::emitTouchEnd(UpdateTouchEvent &event, BaseViewController &controller)
    {
#ifdef MVCGAME_DEBUG_EVENTS
        std::cout << ">>>>" << std::endl;        
        std::cout << "EventEmitter::emitTouchEnd " << std::endl;
        std::cout << event << std::endl;
        std::cout << "<<<<" << std::endl;
#endif

        TouchEvent::Responders list = event.getStart().getResponders();
        TouchEvent::Responders::iterator itr;
        for(itr=list.begin(); itr!=list.end(); ++itr)
        {
            (**itr).respondOnTouchEnd(event);
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

    void EventEmitter::emitTouchUpdate(UpdateTouchEvent& event)
    {
        emitTouchUpdate(event, _root);
    }    
    
    void EventEmitter::emitTouchEnd(UpdateTouchEvent& event)
    {
        emitTouchEnd(event, _root);
    }
    
}