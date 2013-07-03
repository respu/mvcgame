

#include <mvcgame/view/PanZoomView.hpp>
#include <mvcgame/event/Events.hpp>

#include <algorithm>
#include <cassert>

namespace mvcgame {

    PanZoomView::PanZoomView() :
    _touched(false),
    _panInertiaDuration(Duration::secs(0.5)),
    _panSpeedInterval(Duration::secs(0.05))
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
    }

    void PanZoomView::respondOnTouchStart(const TouchEvent& event)
    {
        if(!_contentView)
        {
            return;
        }
        _touched = event.touched(*_contentView);
        if(_touched)
        {
            _touchPoint = event.getTouchPoint(*_contentView);
            _touchPoint -= _contentView->getFrame().origin; 
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

    void PanZoomView::respondOnTouchUpdate(const TouchEvent& event)
    {
        if(!_contentView)
        {
            return;
        }        
        if(_touched && event.touched(*_contentView))
        {
            auto point = event.getTouchPoint(*_contentView);
            _contentView->getFrame().origin = point - _touchPoint;
            _touchTimePoints.push_back(TimePoint(Time::now(), point));
            removeOldTouchTimePoints();            
        }
    }

    void PanZoomView::respondOnTouchEnd(const TouchEvent& event)
    {
        if(_touched)
        {
            TimePoint& start = _touchTimePoints.front();
            TimePoint& end = _touchTimePoints.back();
            Duration duration = end.first-start.first;
            if(duration > Duration())
            {
                _panInertiaSpeed = (end.second-start.second)/duration;
                _panInertiaTime = _panInertiaDuration;
                _touched = false;
                _touchTimePoints.clear();
            }
        }
    }
}