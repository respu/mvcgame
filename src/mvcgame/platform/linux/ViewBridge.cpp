

#include <mvcgame/platform/linux/ViewBridge.hpp>
#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/base/Color.hpp>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

namespace mvcgame {

    void ViewBridge::drawPolygon(const std::vector<Point>& poly, const Color& color)
    {
        glBegin(GL_QUADS);
        glColor3f(color.r, color.g, color.b); 

        for(const Point& p : poly)
        {
            glVertex3f(p.x, p.y, 0.);    
        }   
        glEnd();
    }

}