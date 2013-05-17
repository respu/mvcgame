#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/View.hpp>
#include <mvcgame/event/Events.hpp>
#include <mvcgame/Time.hpp>

#include <assert.h>

namespace mvcgame {

	RootViewController::RootViewController() :
    _view(nullptr), _eventEmitter(*this), _lastUpdateEvent(nullptr), _lastTouchEvent(nullptr)
	{
	}

    const ViewController& RootViewController::getParent() const
    {
		assert(false);
		return *this;
    }

    ViewController& RootViewController::getParent()
    {
    	assert(false);
		return *this;
    }

    void RootViewController::removeFromParent()
    {
    }

    void RootViewController::setParent(ViewController& parent)
    {
    	assert(false);
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