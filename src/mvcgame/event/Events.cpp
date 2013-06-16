
#include <mvcgame/event/Events.hpp>
#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/view/View.hpp>

#include <stdexcept>

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

    UpdateEvent::UpdateEvent() :
    _time(Time::now())
    {
    }

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
    
    TouchEvent::TouchEvent()
    {
    }

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

    TouchEvent TouchEvent::operator*(const Transform& t) const
    {
        TouchEvent ev(*this);
        for(Point& p : ev.getPoints())
        {
            p *= t;
        }
        return ev;
    }

    TouchEvent& TouchEvent::operator*=(const Transform& t)
    {
        for(Point& p : getPoints())
        {
            p *= t;
        } 
        return *this;
    }

    bool TouchEvent::touched(const View& view) const
    {
        return touched(view.getBoundingBox());
    }

    bool TouchEvent::touched(const Rect& frame) const
    {
        std::cout << frame << std::endl;
        for(const Point& p : getPoints())
        {
            std::cout << p << std::endl;
            if(frame.contains(p))
            {
                return true;
            }
        } 
        return false;
    }    

    Point TouchEvent::getTouchPoint(const View& view) const
    {
        return getTouchPoint(view.getBoundingBox());
    }    

    Point TouchEvent::getTouchPoint(const Rect& frame) const
    {
        for(const Point& p : getPoints())
        {
            if(frame.contains(p))
            {
                return p;
            }
        } 
        throw new std::runtime_error("Frame was not touched");
    }

#pragma mark - stream functions

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

}
