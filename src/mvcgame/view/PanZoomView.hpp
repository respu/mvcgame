

#ifndef mvcgame_PanZoomView_hpp
#define mvcgame_PanZoomView_hpp

#include <mvcgame/view/View.hpp>
#include <mvcgame/base/Time.hpp>
#include <mvcgame/base/Easing.hpp>

namespace mvcgame {

    class PanZoomView : public View
    {
    private:
        typedef std::pair<Time,Point> TimePoint;
        typedef std::vector<TimePoint> TimePoints;
        
        TimePoints _touchTimePoints;
        Point _touchPoint;
        bool _touched;

        Speed _panInertiaSpeed;
        float _panInertiaPercent;
        Duration _panInertiaDuration;
        Duration _panSpeedInterval;
        Easing::Function _panInertiaEasing;

        Duration _outOfBoundsDuration;

        std::shared_ptr<View> _contentView;

        void removeOldTouchTimePoints();

        Point getOutOfBoundsDistance();
    public:
        PanZoomView();
        PanZoomView(std::shared_ptr<View> contentView);
        void setContentView(std::shared_ptr<View> contentView);
        
        /**
         * The time between the touch end and a complete stop
         * of the inertia
         */
        void setPanInertiaDuration(Duration d);

        /**
         * The interval of time taken into account to optain
         * the pan speed when the touch ends
         */
        void setPanInertiaSpeedInterval(Duration d);

        /**
         * The time it should take to go from an out of bounds
         * position to the edge of the content view
         */
        void setOutOfBoundsDuration(Duration d);

        void respondOnUpdate(const UpdateEvent& event);
        void respondOnTouchStart(const TouchEvent& event);
        void respondOnTouchUpdate(const TouchEvent& event);
        void respondOnTouchEnd(const TouchEvent& event);
    };
}

#endif