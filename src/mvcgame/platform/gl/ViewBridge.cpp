

#include <mvcgame/platform/gl/ViewBridge.hpp>
#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/base/Color.hpp>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

#ifdef MVCGAME_DEBUG_DRAW
#include <iostream>
#endif

namespace mvcgame {

    void getGlTransform(const Transform& t, float* m)
    {
        m[2] = m[3] = m[6] = m[7] = m[8] = m[9] = m[11] = m[14] = 0.0f;
        m[10] = m[15] = 1.0f;
        m[0] = t.a; m[4] = t.c; m[12] = t.tx;
        m[1] = t.b; m[5] = t.d; m[13] = t.ty;
    }

    void ViewBridge::loadRootTransform(const Size& size)
    {
        Point norm(1, 1);
        Transform transform = norm/Point(size/2);
        transform -= norm;

#ifdef MVCGAME_DEBUG_DRAW
        std::cout << "----" << std::endl;        
        std::cout << "GlViewBridge::loadRootTransform " << std::endl;
        std::cout << size << std::endl;
        std::cout << transform << std::endl;
        std::cout << "----" << std::endl;
#endif
        float glt[16];
        getGlTransform(transform, glt);
        glLoadMatrixf(glt);
    }

    void ViewBridge::pushTransform(const Transform& transform)
    {
#ifdef MVCGAME_DEBUG_DRAW
        std::cout << "----" << std::endl;        
        std::cout << "GlViewBridge::pushTransform " << std::endl;
        std::cout << transform << std::endl;
        std::cout << "----" << std::endl;
#endif
        float glt[16];
        getGlTransform(transform, glt);
        glMultMatrixf(glt);
    }

    void ViewBridge::popTransform(const Transform& transform)
    {
        Transform inverse = transform.invert();
#ifdef MVCGAME_DEBUG_DRAW
        std::cout << "----" << std::endl;
        std::cout << "GlViewBridge::popTransform " << std::endl;
        std::cout << transform << std::endl;
        std::cout << inverse << std::endl;
        std::cout << "----" << std::endl;
#endif
        float glt[16];
        getGlTransform(inverse, glt);
        glMultMatrixf(glt);
    }

    void ViewBridge::drawPolygon(const Points& verts, const Color& color)
    {
#ifdef MVCGAME_DEBUG_DRAW
        std::cout << "----" << std::endl;        
        std::cout << "GlViewBridge::drawPolygon " << color << std::endl;
        for(const Point& p : verts)
        {
            std::cout << p << std::endl;
        }
        std::cout << "----" << std::endl;
#endif

        glBegin(GL_QUADS);
        glColor3f(color.r/255.0f, color.g/255.0f, color.b/255.0f); 

        for(const Point& p : verts)
        {
            glVertex3f(p.x, p.y, 0.);
        }   
        glEnd();
    }

}