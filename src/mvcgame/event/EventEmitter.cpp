
#include <mvcgame/event/EventEmitter.hpp>
#include <mvcgame/event/Events.hpp>
#include <mvcgame/controller/BaseViewController.hpp>
#include <mvcgame/controller/ViewController.hpp>
#include <mvcgame/view/View.hpp>

namespace mvcgame {

    EventEmitter::EventEmitter(BaseViewController& root) : _root(root)
    {
    }

    EventEmitter::~EventEmitter()
    {
    }

    void EventEmitter::emitUpdate(const UpdateEvent& event, BaseViewController& controller)
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

    void EventEmitter::findTouchResponders(const Point& p, const TouchEvent& event, BaseViewController& controller, TouchResponders& responders)
    {
        if(!controller.respondToTouchPoint(p, event))
        {
            return;
        }
        if(event.getStopPropagation())
        {
            return;
        }
        responders[&controller] = event;
        for(const std::unique_ptr<ViewController>& child : controller.getChildren())
        {
            const Transform& t = child->getView().getTransform();
            Point cp = p*t;
            TouchEvent cev = event*t;
            findTouchResponders(cp, cev, *child, responders);
            if(event.getStopPropagation())
            {
                return;
            }
        }
    }

    EventEmitter::TouchResponders EventEmitter::findTouchResponders(const TouchEvent& event, BaseViewController& controller)
    {
        TouchResponders responders;
        TouchEvent::Points::const_iterator itr;
        
        for(const Point& point : event.getPoints())
        {
            findTouchResponders(point, event, controller, responders);
            if(event.getStopPropagation())
            {
                break;
            }
        }

        return responders;
    }
    
    void EventEmitter::emitTouch(const TouchEvent &event, BaseViewController &controller, TouchResponderCallback callback)
    {
        TouchResponders list = findTouchResponders(event, _root);
        if(event.getStopPropagation())
        {
            return;
        }        
        TouchResponders::iterator itr;
        for(itr=list.begin(); itr!=list.end(); ++itr)
        {
            callback(*itr->first, itr->second);
            if(event.getStopPropagation())
            {
                break;
            }
        }
    }

    void EventEmitter::emitUpdate(const UpdateEvent& event)
    {
        emitUpdate(event, _root);
    }

    void EventEmitter::emitTouchStart(const TouchEvent& event)
    {
#ifdef MVCGAME_DEBUG_EVENTS
        std::cout << ">>>>" << std::endl;        
        std::cout << "EventEmitter::emitTouchStart " << std::endl;
        std::cout << event << std::endl;
        std::cout << "<<<<" << std::endl;
#endif        
        emitTouch(event, _root, [](IResponder& responder, const TouchEvent& ev){
            responder.respondOnTouchStart(ev);
        });
    }

    void EventEmitter::emitTouchUpdate(const TouchEvent& event)
    {
#ifdef MVCGAME_DEBUG_EVENTS
        std::cout << ">>>>" << std::endl;        
        std::cout << "EventEmitter::emitTouchUpdate " << std::endl;
        std::cout << event << std::endl;
        std::cout << "<<<<" << std::endl;
#endif
        emitTouch(event, _root, [](IResponder& responder, const TouchEvent& ev){
            responder.respondOnTouchUpdate(ev);
        });
    }    
    
    void EventEmitter::emitTouchEnd(const TouchEvent& event)
    {
#ifdef MVCGAME_DEBUG_EVENTS
        std::cout << ">>>>" << std::endl;        
        std::cout << "EventEmitter::emitTouchEnd " << std::endl;
        std::cout << event << std::endl;
        std::cout << "<<<<" << std::endl;
#endif        
        emitTouch(event, _root, [](IResponder& responder, const TouchEvent& ev){
            responder.respondOnTouchEnd(ev);
        });
    }
    
}