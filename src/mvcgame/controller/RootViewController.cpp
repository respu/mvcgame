#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/base/Application.hpp>
#include <mvcgame/base/Time.hpp>

#include <cassert>
#include <algorithm>

namespace mvcgame {

	RootViewController::RootViewController(Application& app) :
    _app(app), _view(app.getViewBridge()), _eventEmitter(*this),
    _lastUpdateEvent(nullptr), _lastTouchEvent(nullptr)
	{
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

        _view.update();
        _view.draw();
    }

    void RootViewController::emitTouchStart(const Points& points)
    {
        std::unique_ptr<TouchEvent> event(new TouchEvent(points));
        _eventEmitter.emitTouchStart(*event);
        _lastTouchEvent = std::move(event);
    }

    void RootViewController::emitTouchEnd(const Points& points)
    {
        assert(_lastTouchEvent != nullptr);
        EndTouchEvent event(points, *_lastTouchEvent);
        _eventEmitter.emitTouchEnd(event);
        _lastTouchEvent = nullptr;
    }
}