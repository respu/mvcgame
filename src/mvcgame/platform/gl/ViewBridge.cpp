

#include <mvcgame/platform/gl/ViewBridge.hpp>
#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/base/Color.hpp>
#include <mvcgame/texture/Texture.hpp>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

#include <map>

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
        std::cout << ">>>>" << std::endl;        
        std::cout << "GlViewBridge::loadRootTransform " << std::endl;
        std::cout << size << std::endl;
        std::cout << transform << std::endl;
        std::cout << "<<<<" << std::endl;
#endif
        float glt[16];
        getGlTransform(transform, glt);
        glLoadMatrixf(glt);
    }

    void ViewBridge::pushTransform(const Transform& transform)
    {
#ifdef MVCGAME_DEBUG_DRAW
        std::cout << ">>>>" << std::endl;        
        std::cout << "GlViewBridge::pushTransform " << std::endl;
        std::cout << transform << std::endl;
        std::cout << "<<<<" << std::endl;
#endif
        float glt[16];
        getGlTransform(transform, glt);
        glMultMatrixf(glt);
    }

    void ViewBridge::popTransform(const Transform& transform)
    {
        Transform inverse = transform.invert();
#ifdef MVCGAME_DEBUG_DRAW
        std::cout << ">>>>" << std::endl;
        std::cout << "GlViewBridge::popTransform " << std::endl;
        std::cout << transform << std::endl;
        std::cout << inverse << std::endl;
        std::cout << "<<<<" << std::endl;
#endif
        float glt[16];
        getGlTransform(inverse, glt);
        glMultMatrixf(glt);
    }

    void ViewBridge::drawPolygon(const Points& verts, const Color& color)
    {
#ifdef MVCGAME_DEBUG_DRAW
        std::cout << ">>>>" << std::endl;        
        std::cout << "GlViewBridge::drawPolygon " << color << std::endl;
        for(const Point& p : verts)
        {
            std::cout << p << std::endl;
        }
        std::cout << "<<<<" << std::endl;
#endif

        glBegin(GL_QUADS);
        glColor4f(color.r/255.0f, color.g/255.0f, color.b/255.0f, color.a/255.0f); 
        for(const Point& p : verts)
        {
            glVertex3f(p.x, p.y, 0.);
        }
        glEnd();
    }

    typedef std::map<const Texture*, GLuint> Textures;
    static Textures _textures;

    void ViewBridge::loadTexture(const Texture& t)
    {
        Textures::const_iterator itr = _textures.find(&t);
        if(itr != _textures.end())
        {
            return;
        }            
    
        GLuint id;        
        glGenTextures(1, &id);
        _textures.insert(itr, Textures::value_type(&t, id));

        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);        

        GLenum target = GL_TEXTURE_2D;
        GLint level = 0;
        GLsizei width = t.getSize().width;
        GLsizei height = t.getSize().height;
        GLint border = 0;
        GLenum format = t.hasAlpha() ? GL_RGBA : GL_RGB;
        GLenum type = GL_UNSIGNED_BYTE;
        const GLvoid* data = t.getData();

        glTexImage2D(target, level, format, width, height, border, format, type, data);
        
#ifdef MVCGAME_DEBUG_DRAW
        std::cout << ">>>>" << std::endl;
        std::cout << "GlViewBridge::loadTexture " << id << std::endl;
        std::cout << "level " << level << ", ";        
        std::cout << "size " << width << "x" << height << ", ";
        std::cout << "border " << border << ", ";
        std::cout << "format " << format << ", ";
        std::cout << "type " << type << std::endl;
        GLenum err = glGetError();
        if(err != GL_NO_ERROR)
        {
            std::cout << "error " << err << std::endl;
        }
        std::cout << "<<<<" << std::endl;
#endif        
    }

    void ViewBridge::drawTexture(const Rect& rect, const Texture& texture, const Rect& trect)
    {
        loadTexture(texture);
        GLuint id = _textures.at(&texture);

        glEnable(GL_TEXTURE_2D);
        if(texture.hasAlpha())
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        glBindTexture(GL_TEXTURE_2D, id);

        const Size& s = texture.getSize();
        Rect turect(trect.origin.x/s.width, trect.origin.y/s.height,
            trect.size.width/s.width, trect.size.height/s.height);

        glBegin(GL_QUADS);
        glTexCoord2f(turect.origin.x, turect.origin.y);
        glVertex3f(rect.origin.x, rect.origin.y, 0);
        glTexCoord2f(turect.origin.x, turect.origin.y+turect.size.height);
        glVertex3f(rect.origin.x, rect.origin.y+rect.size.height, 0);
        glTexCoord2f(turect.origin.x+turect.size.width, turect.origin.y+turect.size.height);
        glVertex3f(rect.origin.x+rect.size.width, rect.origin.y+rect.size.height, 0);
        glTexCoord2f(turect.origin.x+turect.size.width, turect.origin.y);
        glVertex3f(rect.origin.x+rect.size.width, rect.origin.y, 0);
        glEnd();
        glFlush();

        glDisable(GL_TEXTURE_2D);
        if(texture.hasAlpha())
        {
            glDisable(GL_BLEND);
        }

#ifdef MVCGAME_DEBUG_DRAW
        std::cout << ">>>>" << std::endl;
        std::cout << "GlViewBridge::drawTexture " << id << std::endl;
        std::cout << "rect " << rect << std::endl;
        std::cout << "textureRect " << turect << std::endl;
        GLenum err = glGetError();
        if(err != GL_NO_ERROR)
        {
            std::cout << "error " << err << std::endl;
        }        
        std::cout << "<<<<" << std::endl;
#endif        
    }

}