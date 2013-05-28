
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
    }

    void RootView::addChild(std::unique_ptr<View> child, unsigned layer)
    {
        child->setRoot(*this);
        BaseView::addChild(std::move(child), layer);
    }

    void RootView::draw()
    {
        getBridge().loadRootTransform(_size);
        BaseView::draw();
    }

    IRenderBridge& RootView::getBridge()
    {
        return _bridge;
    }

}