#ifndef mvcgame_RootViewController_hpp
#define mvcgame_RootViewController_hpp

#include <mvcgame/event/EventEmitter.hpp>
#include <mvcgame/event/Events.hpp>
#include <mvcgame/view/RootView.hpp>
#include <mvcgame/controller/BaseViewController.hpp>
#include <mvcgame/controller/ViewController.hpp>

#include <vector>
#include <memory>

namespace mvcgame {

    class Application;
    class Point;
    typedef std::vector<Point> Points;

    class RootViewController : public BaseViewController
    {      
    private:
        Application& _app;
    	RootView _view;
        EventEmitter _eventEmitter;
        std::unique_ptr<UpdateEvent> _lastUpdateEvent;
        std::unique_ptr<TouchEvent> _lastTouchEvent;
        float _frameDelay;
        float _framePassed;
    public:
    	RootViewController(Application& app);

        const RootView& getView() const;
        RootView& getView();

        const Application& getApp() const;
        Application& getApp();

        void addChild(std::unique_ptr<ViewController> child);

        void emitUpdate();
        void emitTouchStart(const Points& points);
        void emitTouchEnd(const Points& points);

        void setFrameDelay(float delay);
    };
}

#endif