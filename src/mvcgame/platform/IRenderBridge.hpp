

#ifndef mvcgame_IRenderBridge_hpp
#define mvcgame_IRenderBridge_hpp

#include <mvcgame/texture/TextureRegion.hpp>
#include <mvcgame/base/Geometry.hpp>

#include <vector>
#include <memory>

namespace mvcgame {

    struct Vertex
    {
        Point position;
        Point texture;
    };    

    class Size;
    class Point;
    class Color;
    class Transform;
    class Texture;
    class Rect;
    class TextureRegion;

    class IRenderBridge
    {
    public:

        typedef std::vector<Point> Points;        
        typedef std::vector<Vertex> Vertices;

    protected:

        Vertices getTextureRectVertices(const Texture& texture, const Rect& rect, const TextureRegion& region);

    public:
        virtual ~IRenderBridge(){};

        /**
         Is called at the beginning of a draw
         */
        virtual void beforeDraw();

        /**
         Is called at the end of a draw
         */
        virtual void afterDraw();        

        /**
         Is called at the beginning of a draw to setup the size
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
        virtual void drawPolygon(const Points& points, const Color& color) = 0;

        /**
         Should draw a texture
         @param texture texture to draw         
         @param vertices pairs of texture and position points
         */
        virtual void drawTexture(std::shared_ptr<const Texture> texture, const Vertices& vertices) = 0;

        /**
         Should draw a texture
         @param texture texture to draw         
         @param rect rectangle with hthe position of the texture
         @param region region inside the texture
         */
        virtual void drawTexture(std::shared_ptr<const Texture> texture, const Rect& rect, const TextureRegion& region);

        /**
         Utility method that will st the texture region to the entire texture
         */
        void drawTexture(std::shared_ptr<const Texture> texture, const Rect& rect);
    };

}

#endif