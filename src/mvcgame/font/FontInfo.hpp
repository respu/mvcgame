  
#ifndef mvcgame_FontInfo_hpp
#define mvcgame_FontInfo_hpp

#include <mvcgame/base/Geometry.hpp>

#include <string>

namespace mvcgame {

    class FontInfo
    {
    public:
        std::string name;
        unsigned size;
        bool bold;
        bool italic;
        RectBorder padding;
        Size spacing;
        float lineHeight;
        float baseHeight;
        Scale scale;
        
        FontInfo();
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const FontInfo& i);
}


#endif