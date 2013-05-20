
#ifndef mvcgame_RootView_hpp
#define mvcgame_RootView_hpp

#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/view/BaseView.hpp>

#include <vector>
#include <memory>

namespace mvcgame {

    class Color;
    class IViewBridge;

    class RootView : public BaseView
    {
    private:
        Size _size;
        IViewBridge& _bridge;
    public:

        RootView(IViewBridge& bridge);

        Size& getSize();
        const Size& getSize() const;
        void setSize(const Size& size);

        void drawPolygon(const std::vector<Point>& poly, const Color& color);
    };
}

#endif