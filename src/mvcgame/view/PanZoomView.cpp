

#include <mvcgame/view/PanZoomView.hpp>
#include <mvcgame/event/Events.hpp>

#include <algorithm>

namespace mvcgame {

    PanZoomView::PanZoomView() :
    _touched(false),
    _panInertiaDuration(Duration::secs(0.5))
    {   
    }

    PanZoomView::PanZoomView(std::shared_ptr<View> contentView) :
    _touched(false),
    _panInertiaDuration(Duration::secs(0.5))  
    {
        setContentView(contentView);
    }

    void PanZoomView::setPanInertiaDuration(Duration d)
    {
        _panInertiaDuration = d;
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
        }
    }

    void PanZoomView::respondOnTouchEnd(const TouchEvent& event)
    {
        if(_touched)
        {
            TimePoint& start = _touchTimePoints.front();
            TimePoint& end = _touchTimePoints.back();
            _panInertiaSpeed = (end.second-start.second)/(end.first-start.first);
            std::cout << _panInertiaSpeed << std::endl;
            _panInertiaTime = _panInertiaDuration;
            _touched = false;
            _touchTimePoints.clear();
        }
    }
}