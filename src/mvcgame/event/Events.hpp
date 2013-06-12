
#ifndef mvcgame_Events_hpp
#define mvcgame_Events_hpp

#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/base/Time.hpp>
#include <vector>
#include <iostream>

namespace mvcgame {
    
    class IResponder;

	class Event
	{
	private:
		bool _stopPropagation;

	public:
		Event();
		virtual ~Event();
		void setStopPropagation(bool value=true);
		bool getStopPropagation() const;
	};

	class UpdateEvent : public Event
	{
	protected:
		Time _time;
		Duration _interval;		
	public:
        UpdateEvent(const Time& t, const Duration& d);
		const Duration& getInterval() const;
		const Time& getTime() const;
	};

	class TouchEvent : public Event
	{
    public:
        typedef std::vector<Point> Points;
        typedef std::vector<IResponder*> Responders;
	private:
		Points _points;
        Responders _responders;
	public:
		TouchEvent(const Points& points);
        virtual ~TouchEvent();
		const Points& getPoints() const;
        Points& getPoints();
		const Responders& getResponders() const;
        Responders& getResponders();
        void addResponder(IResponder& responder);
	};
    
	class UpdateTouchEvent : public TouchEvent
	{
    private:
		TouchEvent& _start;
    public:
		UpdateTouchEvent(const Points& points, TouchEvent& start);
        const TouchEvent& getStart() const;
        TouchEvent& getStart();
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const UpdateEvent& e);
    std::ostream& operator<<(std::ostream& os, const TouchEvent& e);
    std::ostream& operator<<(std::ostream& os, const UpdateTouchEvent& e);
}

#endif
