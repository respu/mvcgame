

#ifndef mvcgame_PanZoomView_hpp
#define mvcgame_PanZoomView_hpp

#include <mvcgame/view/View.hpp>
#include <mvcgame/base/Time.hpp>
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
        Duration _panInertiaTime;
        Duration _panInertiaDuration;
        Duration _panSpeedInterval;

        std::shared_ptr<View> _contentView;

        void removeOldTouchTimePoints();
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

        void respondOnUpdate(const UpdateEvent& event);
        void respondOnTouchStart(const TouchEvent& event);
        void respondOnTouchUpdate(const TouchEvent& event);
        void respondOnTouchEnd(const TouchEvent& event);
    };
}

#endif