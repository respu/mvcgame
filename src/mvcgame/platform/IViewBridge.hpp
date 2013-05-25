

#ifndef mvcgame_IViewBridge_hpp
#define mvcgame_IViewBridge_hpp

#include <string>
#include <vector>

namespace mvcgame {

    class Size;
    class Point;
    class Color;
    class Transform;
    class Texture;
    class Rect;
    typedef std::vector<Point> Points;

    class IViewBridge
    {
    public:
        virtual ~IViewBridge(){};

        /**
         Is called at the beginning of the app to setup the size
         */
        virtual void loadRootTransform(const Size& size) = 0;

        /**
         Is called before every view draw to change the transform
         */
        virtual void pushTransform(const Transform& transform) = 0;

        /**
         Is called after every view draw to revert the transform
         */
        virtual void popTransform(const Transform& transform) = 0;        

        /**
         Should draw a polygon of a given color
         */
        virtual void drawPolygon(const Points& vertices, const Color& color) = 0;

        /**
         Should load a texture
         */
        virtual void loadTexture(const Texture& texture) = 0;

        /**
         Should draw a texture, the texture should be loaded if it isn't already
         @param rectangle wit hthe position of the texture
         @param texture to draw
         @param rectangle inside the texture
         */
        virtual void drawTexture(const Rect& rect, const Texture& texture, const Rect& textureRect) = 0;

        /**
         Utility method that will st the texture rectangle to the entire texture
         */
        void drawTexture(const Rect& rect, const Texture& texture);
    };

}

#endif