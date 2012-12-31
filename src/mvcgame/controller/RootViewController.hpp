#ifndef mvcgame_RootViewController_hpp
#define mvcgame_RootViewController_hpp

#include <mvcgame/controller/BaseViewController.hpp>
#include <mvcgame/event/EventEmitter.hpp>
#include <memory>

namespace mvcgame {

    class UpdateEvent;
    class TouchEvent;
    class Point;
    typedef std::vector<Point> Points;

    class RootViewController : public BaseViewController
    {
    private:
    	IViewPtr _view;
        EventEmitter _eventEmitter;
        std::unique_ptr<UpdateEvent> _lastUpdateEvent;
        std::unique_ptr<TouchEvent> _lastTouchEvent;

    public:
    	RootViewController();
    	~RootViewController();

        const IView& getView() const;
        IView& getView();
        void setView(IViewPtr view);

        const IViewController& getParent() const;
        IViewController& getParent();
        void setParent(IViewController& parent);
        void removeFromParent();

        void emitUpdate();
        void emitTouchStart(const Points& points);
        void emitTouchEnd(const Points& points);
    };
}

#endif