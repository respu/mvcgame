
#ifndef mvcgame_Events_hpp
#define mvcgame_Events_hpp

#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/base/Time.hpp>
#include <vector>
#include <iostream>

namespace mvcgame {
    
    class IResponder;
    class Transform;
    class View;

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
        UpdateEvent();
        UpdateEvent(const Time& t, const Duration& d);
		const Duration& getInterval() const;
		const Time& getTime() const;
	};

	class TouchEvent : public Event
	{
    public:
        typedef std::vector<Point> Points;
	private:
		Points _points;
	public:
        TouchEvent();
		TouchEvent(const Points& points);
        virtual ~TouchEvent();
		const Points& getPoints() const;
        Points& getPoints();

        bool touched(const Rect& frame) const;
        bool touched(const View& view) const;
        Point getTouchPoint(const Rect& frame) const;
        Point getTouchPoint(const View& view) const;

        TouchEvent operator*(const Transform& t) const;
        TouchEvent& operator*=(const Transform& t);
	};

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const UpdateEvent& e);
    std::ostream& operator<<(std::ostream& os, const TouchEvent& e);
}

#endif
