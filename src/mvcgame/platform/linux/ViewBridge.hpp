#ifndef mvcgame_linux_ViewBridge_hpp
#define mvcgame_linux_ViewBridge_hpp

#include <mvcgame/platform/IViewBridge.hpp>

namespace mvcgame {

    class ViewBridge : public IViewBridge
    {
    public:
        void drawPolygon(const std::vector<Point>& poly, const Color& color);
    };

}

#endif