

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

    RenderBridge::RenderBridge()
    {
    }

    void RenderBridge::getGlTransform(const Transform& t, float* m)
    {
        m[2] = m[3] = m[6] = m[7] = m[8] = m[9] = m[11] = m[14] = 0.0f;
        m[10] = m[15] = 1.0f;
        m[0] = t.a; m[4] = t.c; m[12] = t.tx;
        m[1] = t.b; m[5] = t.d; m[13] = t.ty;
    }    

    void RenderBridge::setTransform(const Transform& transform)
    {
#ifdef MVCGAME_DEBUG_DRAW
        std::cout << ">>>>" << std::endl;
        std::cout << "GlRenderBridge::setTransform " << std::endl;
        std::cout << transform << std::endl;
        std::cout << "<<<<" << std::endl;
#endif
        _transform = transform;
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
        for(const Point& point : verts)
        {
            Point p = point*_transform;
            glVertex3f(p.x, p.y, 0.0f);
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

    void RenderBridge::drawTexture(std::shared_ptr<const Texture> texture, const Rect& rect, const TextureRegion& region)
    {
        IRenderBridge::drawTexture(texture, rect, region);
    }

    void RenderBridge::drawTexture(std::shared_ptr<const Texture> texture, const Vertices& vertices)
    {
        loadTexture(*texture);
        GLuint textureId = _textures.at(texture.get());

        FloatList texturesBuffer(2*vertices.size());
        FloatList verticesBuffer(3*vertices.size());
        for(const Vertex& vertex : vertices)
        {
            Point p = vertex.position*_transform;
            texturesBuffer.push_back(vertex.texture.x);
            texturesBuffer.push_back(vertex.texture.y);
            verticesBuffer.push_back(p.x);
            verticesBuffer.push_back(p.y);
            verticesBuffer.push_back(0);
        }

        glEnable(GL_TEXTURE_2D);
        glEnableClientState( GL_TEXTURE_COORD_ARRAY );
        glEnableClientState( GL_VERTEX_ARRAY );

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);       

        glBindTexture(GL_TEXTURE_2D, textureId);
        glVertexPointer(3, GL_FLOAT, 0, &verticesBuffer.front() );
        glTexCoordPointer(2, GL_FLOAT, 0, &texturesBuffer.front() );
        glDrawArrays(GL_QUADS, 0, verticesBuffer.size()/3 );

        glDisableClientState( GL_TEXTURE_COORD_ARRAY );
        glDisableClientState( GL_VERTEX_ARRAY );
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
        glFlush();

#ifdef MVCGAME_DEBUG_DRAW
        std::cout << ">>>>" << std::endl;
        std::cout << "GlRenderBridge::drawTexture " << textureId << std::endl;
        std::cout << "vertices " << vertices.size() << std::endl;
        GLenum err = glGetError();
        if(err != GL_NO_ERROR)
        {
            std::cout << "error " << err << std::endl;
        }        
        std::cout << "<<<<" << std::endl;
#endif        
    }

}