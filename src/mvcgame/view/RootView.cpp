
#include <mvcgame/view/RootView.hpp>
#include <mvcgame/view/View.hpp>
#include <mvcgame/platform/IRenderBridge.hpp>

namespace mvcgame {

    RootView::RootView(IRenderBridge& bridge) :
     _bridge(bridge)
    {
    }

    Size& RootView::getSize()
    {
        return _size;
    }

    const Size& RootView::getSize() const
    {
        return _size;
    }

    void RootView::setSize(const Size& size)
    {
        _size = size;

        Point norm(1, 1);
        _transform = Transform(norm/Point(_size/2)) - norm;
    }

    const Transform& RootView::getTransform() const
    {
        return _transform;
    }

    void RootView::addChild(std::shared_ptr<View> view, unsigned layer)
    {
        view->setRoot(*this);
        BaseView::addChild(view, layer);
    }

    void RootView::draw()
    {
        getBridge().beforeDraw();
        BaseView::draw();
        getBridge().afterDraw();
    }

    IRenderBridge& RootView::getBridge()
    {
        return _bridge;
    }

    bool RootView::respondToTouchPoint(const Point& p, const TouchEvent& event)
    {
        return true;
    }
}