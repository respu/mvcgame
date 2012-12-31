#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/IView.hpp>
#include <mvcgame/event/Events.hpp>
#include <mvcgame/Time.hpp>

#include <assert.h>

namespace mvcgame {

	RootViewController::RootViewController() :
    _view(nullptr), _eventEmitter(*this), _lastUpdateEvent(nullptr), _lastTouchEvent(nullptr)
	{
	}

	RootViewController::~RootViewController()
	{
        clearChildren();
	}

    const IView& RootViewController::getView() const
    {
    	assert(_view != nullptr);
		return *_view;
    }

    IView& RootViewController::getView()
    {
    	assert(_view != nullptr);
    	return *_view;
    }

    const IViewController& RootViewController::getParent() const
    {
		assert(false);
    }

    IViewController& RootViewController::getParent()
    {
    	assert(false);
    }

    void RootViewController::removeFromParent()
    {
    }

    void RootViewController::setParent(IViewController& parent)
    {
    	assert(false);
    }

    void RootViewController::setView(IViewPtr view)
    {
        // set new view pointer
        IViewPtr oldView = std::move(_view);
        _view = std::move(view);

        if(oldView != nullptr)
        {
            moveChildren(*oldView);
        }
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