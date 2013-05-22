

#ifndef mvcgame_IViewBridge_hpp
#define mvcgame_IViewBridge_hpp

#include <string>
#include <vector>

namespace mvcgame {

    class Size;
    class Point;
    class Color;
    class Transform;
    typedef std::vector<Point> Points;

    class IViewBridge
    {
    public:
        virtual ~IViewBridge(){};
        virtual void loadRootTransform(const Size& size) = 0;
        virtual void pushTransform(const Transform& transform) = 0;
        virtual void popTransform(const Transform& transform) = 0;        
        virtual void drawPolygon(const Points& vertices, const Color& color) = 0;
    };

}

#endif