#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/base/Application.hpp>
#include <mvcgame/base/Time.hpp>

#include <cassert>
#include <algorithm>

namespace mvcgame {

	RootViewController::RootViewController(Application& app) :
    _app(app), _view(app.getBridge().getRender()), _eventEmitter(*this, _view),
    _lastUpdateEvent(nullptr), _lastTouchEvent(nullptr),
    _frameDelay(1.0f/60.0f), _framePassed(0.0f)
	{
	}

    void RootViewController::setFrameDelay(float delay)
    {
        _frameDelay = delay;
    }

    const RootView& RootViewController::getView() const
    {
        return _view;
    }

    RootView& RootViewController::getView()
    {
        return _view;
    }

    void RootViewController::addChild(std::unique_ptr<ViewController> child)
    {   
        child->setRoot(*this);        
        BaseViewController::addChild(std::move(child));
    }

    const Application& RootViewController::getApp() const
    {
        return _app;
    }

    Application& RootViewController::getApp()
    {
        return _app;
    }

    void RootViewController::emitUpdate()
    {
        Time now = Time::now();
        Time last = Time::now();
        if(_lastUpdateEvent != nullptr)
        {
            last = _lastUpdateEvent->getTime();
        }
        std::unique_ptr<UpdateEvent> event(new UpdateEvent(now, now-last));
        _eventEmitter.emitUpdate(*event);
        _lastUpdateEvent = std::move(event);

        _framePassed += _lastUpdateEvent->getInterval().fsecs();
        if(_framePassed > _frameDelay)
        {
            _view.update();
            _framePassed = 0.0f;
            _view.draw();            
        }
    }

    void RootViewController::emitTouchStart(const Points& points)
    {
        std::unique_ptr<TouchEvent> event(new TouchEvent(points));
        _eventEmitter.emitTouchStart(*event);
        _lastTouchEvent = std::move(event);
    }

    void RootViewController::emitTouchUpdate(const Points& points)
    {
        assert(_lastTouchEvent != nullptr);
        TouchEvent event(points);
        _eventEmitter.emitTouchUpdate(event);
    }    

    void RootViewController::emitTouchEnd(const Points& points)
    {
        assert(_lastTouchEvent != nullptr);
        TouchEvent event(points);
        _eventEmitter.emitTouchEnd(event);
        _lastTouchEvent = nullptr;
    }

    bool RootViewController::respondToTouchPoint(const Point& p, const TouchEvent& event)
    {
        return true;
    }
}