
#include <mvcgame/view/RootView.hpp>
#include <mvcgame/platform/IViewBridge.hpp>
#include <mvcgame/base/Application.hpp>

namespace mvcgame {

        RootView::RootView(IViewBridge& bridge) :
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

        void RootView::drawPolygon(const std::vector<Point>& poly, const Color& color)
        {
            _bridge.drawPolygon(poly, color);
        }
}