
#ifndef mvcgame_RootView_hpp
#define mvcgame_RootView_hpp

#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/view/BaseView.hpp>

#include <vector>
#include <memory>

namespace mvcgame {

    class Color;
    class IRenderBridge;

    class RootView : public BaseView
    {
    private:
        Size _size;
        IRenderBridge& _bridge;
    public:
        RootView(IRenderBridge& bridge);

        Size& getSize();
        const Size& getSize() const;
        void setSize(const Size& size);

        void addChild(std::shared_ptr<View> view, unsigned layer=0);

        void draw();

        IRenderBridge& getBridge();

        bool respondToTouchPoint(const Point& p, const TouchEvent& event);
    };
}

#endif