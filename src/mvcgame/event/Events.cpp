
#include <mvcgame/event/Events.hpp>

namespace mvcgame {
    
#pragma mark - Event
    
    Event::Event() :
    _stopPropagation(false)
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
    
#pragma mark - UpdateTouchEvent
    
    UpdateTouchEvent::UpdateTouchEvent(const Points& points, TouchEvent& start) :
    TouchEvent(points), _start(start)
    {
    }
    
    const TouchEvent& UpdateTouchEvent::getStart() const
    {
        return _start;
    }
    
    TouchEvent& UpdateTouchEvent::getStart()
    {
        return _start;
    }


    std::ostream& operator<<(std::ostream& os, const UpdateEvent& e)
    {
        os << "UpdateEvent( ";
        if(e.getStopPropagation())
        {
            os << "stopped";
        }
        os << std::endl << e.getInterval() << std::endl;
        os << e.getTime() << std::endl;
        os << ")";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const TouchEvent& e)
    {
        os << "TouchEvent( ";
        if(e.getStopPropagation())
        {
            os << "stopped";
        }
        os << std::endl;
        for(const Point& p : e.getPoints())
        {
            os << p << std::endl;
        }
        os << ")";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const UpdateTouchEvent& e)
    {
        os << "UpdateTouchEvent( ";
        if(e.getStopPropagation())
        {
            os << "stopped";
        }
        os << std::endl;
        for(const Point& p : e.getPoints())
        {
            os << p << std::endl;
        }
        os << "start:" << e.getStart();
        os << ")";
        return os;
    }
}
