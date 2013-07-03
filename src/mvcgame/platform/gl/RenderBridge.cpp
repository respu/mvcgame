

#include <mvcgame/platform/gl/RenderBridge.hpp>
#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/base/Color.hpp>
#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/texture/TextureRegion.hpp>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

#ifdef MVCGAME_DEBUG_DRAW
#include <iostream>
#endif

namespace mvcgame {

    RenderBridge::RenderBridge() :
    _texture(0)
    {
    }

    void RenderBridge::getGlTransform(const Transform& t, float* m)
    {
        m[2] = m[3] = m[6] = m[7] = m[8] = m[9] = m[11] = m[14] = 0.0f;
        m[10] = m[15] = 1.0f;
        m[0] = t.a; m[4] = t.c; m[12] = t.tx;
        m[1] = t.b; m[5] = t.d; m[13] = t.ty;
    }    

    void RenderBridge::loadRootTransform(const Size& size)
    {
        Point norm(1, 1);
        Transform transform = norm/Point(size/2);
        transform -= norm;

#ifdef MVCGAME_DEBUG_DRAW
        std::cout << ">>>>" << std::endl;        
        std::cout << "GlRenderBridge::loadRootTransform " << std::endl;
        std::cout << size << std::endl;
        std::cout << transform << std::endl;
        std::cout << "<<<<" << std::endl;
#endif
        float glt[16];
        getGlTransform(transform, glt);
        glLoadMatrixf(glt);
    }

    void RenderBridge::pushTransform(const Transform& transform)
    {
#ifdef MVCGAME_DEBUG_DRAW
        std::cout << ">>>>" << std::endl;        
        std::cout << "GlRenderBridge::pushTransform " << std::endl;
        std::cout << transform << std::endl;
        std::cout << "<<<<" << std::endl;
#endif
        float glt[16];
        getGlTransform(transform, glt);
        glPushMatrix();
        glMultMatrixf(glt);
    }

    void RenderBridge::popTransform(const Transform& transform)
    {
#ifdef MVCGAME_DEBUG_DRAW
        std::cout << ">>>>" << std::endl;
        std::cout << "GlRenderBridge::popTransform " << std::endl;
        std::cout << transform << std::endl;
        std::cout << "<<<<" << std::endl;
#endif
        glPopMatrix();
    }

    void RenderBridge::drawPolygon(const Points& verts, const Color& color)
    {
#ifdef MVCGAME_DEBUG_DRAW
        std::cout << ">>>>" << std::endl;        
        std::cout << "GlRenderBridge::drawPolygon " << color << std::endl;
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
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f); 
        glEnd();
    }

    void RenderBridge::loadTexture(const Texture& t)
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
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);        

        GLenum target = GL_TEXTURE_2D;
        GLint level = 0;
        GLsizei width = t.getWidth();
        GLsizei height = t.getHeight();
        GLint border = 0;
        GLenum format = t.hasAlpha() ? GL_RGBA : GL_RGB;
        GLenum type = GL_UNSIGNED_BYTE;
        const GLvoid* data = t.getData();

        glTexImage2D(target, level, format, width, height, border, format, type, data);
        
#ifdef MVCGAME_DEBUG_DRAW
        std::cout << ">>>>" << std::endl;
        std::cout << "GlRenderBridge::loadTexture " << id << std::endl;
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

    void RenderBridge::drawTexture(const Rect& rect, const Texture& texture, const TextureRegion& region)
    {
        loadTexture(texture);
        GLuint id = _textures.at(&texture);

        Rect trect = region / texture;
        Rect rrect = region / rect;

        if(region.rotate)
        {
            _textureBuffer =
            {
                trect.origin.x+trect.size.width, trect.origin.y,        
                trect.origin.x+trect.size.width, trect.origin.y+trect.size.height,
                trect.origin.x, trect.origin.y+trect.size.height,            
                trect.origin.x, trect.origin.y,                
            };
        }     
        else
        {
            _textureBuffer =
            {
                trect.origin.x, trect.origin.y,
                trect.origin.x+trect.size.width, trect.origin.y,        
                trect.origin.x+trect.size.width, trect.origin.y+trect.size.height,
                trect.origin.x, trect.origin.y+trect.size.height,            
            };
        }   

        _vertexBuffer =
        {
            rrect.origin.x, rrect.origin.y, 0,
            rrect.origin.x+rrect.size.width, rrect.origin.y, 0,
            rrect.origin.x+rrect.size.width, rrect.origin.y+rrect.size.height, 0,
            rrect.origin.x, rrect.origin.y+rrect.size.height, 0,
        };

        glEnable(GL_TEXTURE_2D);
        glEnableClientState( GL_TEXTURE_COORD_ARRAY );
        glEnableClientState( GL_VERTEX_ARRAY );

        if(texture.hasAlpha())
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }        

        if(_texture != id)
        {
            glBindTexture(GL_TEXTURE_2D, id);
            _texture = id;
        }
        glVertexPointer(3, GL_FLOAT, 0, &_vertexBuffer.front() );
        glTexCoordPointer(2, GL_FLOAT, 0, &_textureBuffer.front() );
        glDrawArrays(GL_QUADS, 0, 4 );

        glDisableClientState( GL_TEXTURE_COORD_ARRAY );
        glDisableClientState( GL_VERTEX_ARRAY );
        glDisable(GL_TEXTURE_2D);
        if(texture.hasAlpha())
        {
            glDisable(GL_BLEND);
        }

        glFlush();            

        if(region.rotate)
        {
            glPopMatrix();
        }


#ifdef MVCGAME_DEBUG_DRAW
        std::cout << ">>>>" << std::endl;
        std::cout << "GlRenderBridge::drawTexture " << id << std::endl;
        std::cout << "rect " << rect << std::endl;
        std::cout << "region " << region << std::endl;
        GLenum err = glGetError();
        if(err != GL_NO_ERROR)
        {
            std::cout << "error " << err << std::endl;
        }        
        std::cout << "<<<<" << std::endl;
#endif        
    }

}