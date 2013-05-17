#ifndef mvcgame_RootViewController_hpp
#define mvcgame_RootViewController_hpp

#include <mvcgame/controller/ViewController.hpp>
#include <mvcgame/event/EventEmitter.hpp>
#include <memory>

namespace mvcgame {

    class UpdateEvent;
    class TouchEvent;
    class Point;
    typedef std::vector<Point> Points;

    class RootViewController : public ViewController
    {
    private:
    	std::unique_ptr<View> _view;
        EventEmitter _eventEmitter;
        std::unique_ptr<UpdateEvent> _lastUpdateEvent;
        std::unique_ptr<TouchEvent> _lastTouchEvent;

    public:
    	RootViewController();

        const ViewController& getParent() const;
        ViewController& getParent();
        void setParent(ViewController& parent);
        void removeFromParent();

        void emitUpdate();
        void emitTouchStart(const Points& points);
        void emitTouchEnd(const Points& points);
    };
}

#endif