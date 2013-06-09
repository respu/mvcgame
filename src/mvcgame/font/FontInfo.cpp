
#include <mvcgame/font/FontInfo.hpp>

namespace mvcgame {

    FontInfo::FontInfo() :
    size(0), bold(false), italic(false),
    lineHeight(0), baseHeight(0)
    {
    }

    std::ostream& operator<<(std::ostream& os, const FontInfo& i)
    {
        os << "FontInfo( " << i.name << std::endl;
        os << "size " << i.size << std::endl;
        if(i.bold)
        {
            os << " bold" << std::endl;
        }
        if(i.italic)
        {
            os << " italic" << std::endl;
        }        
        os << "padding " << i.padding << std::endl;
        os << "spacing " << i.spacing << std::endl;
        os << "scale " << i.scale << std::endl;
        os << "height " << i.lineHeight << ":" << i.baseHeight << std::endl;
        os << ")";
        return os;
    }
}