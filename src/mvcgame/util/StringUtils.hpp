
#ifndef mvcgame_StringUtils_hpp
#define mvcgame_StringUtils_hpp

#include <string>

namespace mvcgame {

    class StringUtils
    {
    public:

        // trim from start
        static void ltrim(std::string &s);

        // trim from end
        static void rtrim(std::string &s);

        // trim from both ends
        static void trim(std::string &s);        
    };

}

#endif