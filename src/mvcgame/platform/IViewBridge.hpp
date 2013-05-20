

#ifndef mvcgame_IViewBridge_hpp
#define mvcgame_IViewBridge_hpp

#include <string>
#include <vector>

namespace mvcgame {

    class Point;
    class Color;

    class IViewBridge
    {
    public:
        virtual ~IViewBridge(){};
        virtual void drawPolygon(const std::vector<Point>& poly, const Color& color) = 0;
    };

}

#endif