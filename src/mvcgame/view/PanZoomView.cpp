

#include <mvcgame/view/PanZoomView.hpp>
#include <mvcgame/event/Events.hpp>

#include <algorithm>
#include <cassert>

namespace mvcgame {

    PanZoomView::PanZoomView() :
    _touched(false),
    _panInertiaDuration(Duration::secs(0.5)),
    _panSpeedInterval(Duration::secs(0.2))
    {   
    }

    PanZoomView::PanZoomView(std::shared_ptr<View> contentView) :
    PanZoomView()
    {
        setContentView(contentView);
    }

    void PanZoomView::setPanInertiaDuration(Duration d)
    {
        _panInertiaDuration = d;
    }

    void PanZoomView::setPanInertiaSpeedInterval(Duration d)
    {
        _panSpeedInterval = d;
    }

    void PanZoomView::setContentView(std::shared_ptr<View> contentView)
    {
        _contentView = contentView;
        addChild(_contentView);
    }

    void PanZoomView::respondOnUpdate(const UpdateEvent& event)
    {     
        if(!_contentView)
        {
            return;
        }       
        if(_panInertiaTime > Duration())
        { 
            _panInertiaTime -= event.getInterval();
            float f = _panInertiaTime / _panInertiaDuration;            
            Point p = (_panInertiaSpeed*f)*event.getInterval();
            _contentView->getFrame().origin += p;
        }
        else
        {
            _panInertiaSpeed = Speed(0, 0);
            bool outOfBounds = false;
            Rect contentBounds = _contentView->getBoundingBox();
            Rect containerBounds = getBoundingBox();
            Point contentOrigin = contentBounds.origin;
            Point containerOrigin = containerBounds.origin;
            Point contentOuter = contentBounds.getOuter();
            Point containerOuter = containerBounds.getOuter();

            if(contentOrigin.x < containerOrigin.x && contentOuter.x < containerOuter.x)
            {
                // to the left
                _panInertiaSpeed.x = (containerOuter.x - contentOuter.x);
                outOfBounds = true;
            }
            if(contentOrigin.x > containerOrigin.x && contentOuter.x > containerOuter.x)
            {
                // to the right
                _panInertiaSpeed.x = (containerOrigin.x - contentOrigin.x);
                outOfBounds = true;
            }
            if(contentOrigin.y < containerOrigin.y && contentOuter.y < containerOuter.y)
            {
                // to the bottom
                _panInertiaSpeed.y = (containerOuter.y - contentOuter.y);
                outOfBounds = true;
            }
            if(contentOrigin.y > containerOrigin.y && contentOuter.y > containerOuter.y)
            {
                // to the top
                _panInertiaSpeed.y = (containerOrigin.y - contentOrigin.y);
                outOfBounds = true;
            }
            if(outOfBounds)
            {
                _panInertiaSpeed /= _panInertiaDuration.fsecs()*_panInertiaDuration.fsecs();
                _panInertiaTime = _panInertiaDuration;
            }
        }
    }

    void PanZoomView::removeOldTouchTimePoints()
    {
        Time threshold = Time::now() - _panSpeedInterval;
        _touchTimePoints.erase(std::remove_if(_touchTimePoints.begin(), _touchTimePoints.end(),
            [&threshold](const TimePoint& tp){
                return tp.first < threshold;
        }), _touchTimePoints.end());
    }    

    void PanZoomView::respondOnTouchStart(const TouchEvent& event)
    {
        if(!_contentView)
        {
            return;
        }
        assert(event.touched(*this));
        _touchPoint = event.getTouchPoint(*this);
    }

    void PanZoomView::respondOnTouchUpdate(const TouchEvent& event)
    {
        if(!_contentView)
        {
            return;
        }
        assert(event.touched(*this));
        auto point = event.getTouchPoint(*this);
        _contentView->getFrame().origin += point - _touchPoint;
        _touchPoint = point;
        _touchTimePoints.push_back(TimePoint(Time::now(), point));
        removeOldTouchTimePoints();
    }

    void PanZoomView::respondOnTouchEnd(const TouchEvent& event)
    {       
        assert(event.touched(*this));
        TimePoint& start = _touchTimePoints.front();
        TimePoint& end = _touchTimePoints.back();
        Duration duration = end.first-start.first;
        assert(duration > Duration());
        _panInertiaSpeed = (end.second-start.second)/duration;
        _panInertiaTime = _panInertiaDuration;
        _touched = false;
        _touchTimePoints.clear();
    }
}