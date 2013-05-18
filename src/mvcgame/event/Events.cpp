
#include <mvcgame/event/Events.hpp>

namespace mvcgame {
    
#pragma mark - Event
    
    Event::Event()
    {
    }
    
    Event::~Event()
    {
        
    }
    
    void Event::setStopPropagation(bool value)
    {
        _stopPropagation = value;
    }
    
    bool Event::getStopPropagation() const
    {
        return _stopPropagation;
    }
    
#pragma mark - UpdateEvent

    UpdateEvent::UpdateEvent(const Time& t, const Duration& d) :
    _time(t), _interval(d)
    {
        
    }
    
    const Duration& UpdateEvent::getInterval() const
    {
        return _interval;
    }
    
    const Time& UpdateEvent::getTime() const
    {
        return _time;
    }

#pragma mark - TouchEvent
    
    TouchEvent::TouchEvent(const Points& points) : _points(points)
    {
    }
    
    TouchEvent::~TouchEvent()
    {
    }
    
    const TouchEvent::Points& TouchEvent::getPoints() const
    {
        return _points;
    }
    
    TouchEvent::Points& TouchEvent::getPoints()
    {
        return _points;
    }
    
    const TouchEvent::Responders& TouchEvent::getResponders() const
    {
        return _responders;
    }
    
    TouchEvent::Responders& TouchEvent::getResponders()
    {
        return _responders;
    }
    
    void TouchEvent::addResponder(IResponder& responder)
    {
        _responders.push_back(&responder);
    }
    
#pragma mark - EndTouchEvent
    
    EndTouchEvent::EndTouchEvent(const Points& points, TouchEvent& start) :
    TouchEvent(points), _start(start)
    {
    }
    
    const TouchEvent& EndTouchEvent::getStart() const
    {
        return _start;
    }
    
    TouchEvent& EndTouchEvent::getStart()
    {
        return _start;
    }
}
