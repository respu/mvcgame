//
//  Events.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_Events_hpp
#define mvcgame_Events_hpp

#include <mvcgame/Geometry.hpp>
#include <mvcgame/Time.hpp>
#include <vector>

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
    
	class EndTouchEvent : public TouchEvent
	{
    private:
		TouchEvent& _start;
    public:
		EndTouchEvent(const Points& points, TouchEvent& start);
        const TouchEvent& getStart() const;
        TouchEvent& getStart();
    };

}

#endif
