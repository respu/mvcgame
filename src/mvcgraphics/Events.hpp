//
//  Events.hpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef __hydra__Events__
#define __hydra__Events__

#include <mvcgraphics/Geometry.hpp>
#include <mvcgraphics/Time.hpp>
#include <vector>

namespace mvcgraphics {
    
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
		Duration _interval;
		Time _time;
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
