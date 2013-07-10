

#include <mvcgame/view/PanZoomView.hpp>
#include <mvcgame/event/Events.hpp>

#include <algorithm>
#include <cassert>

namespace mvcgame {

    PanZoomView::PanZoomView() :
    _touched(false),
    _panInertiaPercent(0),    
    _panInertiaDuration(Duration::secs(0.5)),
    _panSpeedInterval(Duration::secs(0.2)),
    _panInertiaEasing(Easing::linear),
    _outOfBoundsDuration(Duration::secs(0.1))
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
        Speed speed;
        Point outOfBounds = getOutOfBoundsDistance();
        if(outOfBounds)
        {
            _panInertiaSpeed = Speed();
            if(_outOfBoundsDuration)
            {
                speed += outOfBounds/_outOfBoundsDuration;
            }
            else
            {
                _contentView->getFrame().origin += outOfBounds;
            }
        }
        if(_panInertiaSpeed != Speed())
        { 
            _panInertiaPercent += event.getInterval() / _panInertiaDuration;
            speed += Easing::get(
                _panInertiaPercent,
                _panInertiaSpeed,
                _panInertiaSpeed*-1,
                _panInertiaEasing);
            if(_panInertiaPercent>=1)
            {
                _panInertiaSpeed = Speed();
            }
        }

        _contentView->getFrame().origin += speed*event.getInterval();
    }

    Point PanZoomView::getOutOfBoundsDistance()
    {
        Point outOfBounds;
        Rect contentBounds = _contentView->getBoundingBox();
        Rect containerBounds = getBoundingBox();
        Point contentOrigin = contentBounds.origin;
        Point containerOrigin = containerBounds.origin;
        Point contentOuter = contentBounds.getOuter();
        Point containerOuter = containerBounds.getOuter();

        if(contentOrigin.x < containerOrigin.x && contentOuter.x < containerOuter.x)
        {
            // to the left
            outOfBounds.x += (containerOuter.x - contentOuter.x);
        }
        if(contentOrigin.x > containerOrigin.x && contentOuter.x > containerOuter.x)
        {
            // to the right
            outOfBounds.x += (containerOrigin.x - contentOrigin.x);
        }
        if(contentOrigin.y < containerOrigin.y && contentOuter.y < containerOuter.y)
        {
            // to the bottom
            outOfBounds.y += (containerOuter.y - contentOuter.y);
        }
        if(contentOrigin.y > containerOrigin.y && contentOuter.y > containerOuter.y)
        {
            // to the top
            outOfBounds.y += (containerOrigin.y - contentOrigin.y);
        }
        return outOfBounds;
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
        assert(event.touched(*this));
        _touchPoint = event.getTouchPoint(*this);
    }

    void PanZoomView::respondOnTouchUpdate(const TouchEvent& event)
    {
        assert(event.touched(*this));
        auto point = event.getTouchPoint(*this);
        if(_contentView)
        {
            _contentView->getFrame().origin += point - _touchPoint;
        }
        _touchPoint = point;
        _touchTimePoints.push_back(TimePoint(Time::now(), point));
        removeOldTouchTimePoints();
    }

    void PanZoomView::respondOnTouchEnd(const TouchEvent& event)
    {       
        assert(event.touched(*this));
        if(_touchTimePoints.size()>1)
        {
            TimePoint& start = _touchTimePoints.front();
            TimePoint& end = _touchTimePoints.back();
            Duration duration = end.first-start.first;
            assert(duration > Duration());
            _panInertiaSpeed = (end.second-start.second)/duration;
            _panInertiaPercent = 0;
        }
        _touched = false;
        _touchTimePoints.clear();
    }
}