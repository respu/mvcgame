
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

        // encode base64
        static std::string base64Encode(const std::string& s);

        // decode base64
        static std::string base64Decode(const std::string& s);

        // compress data
        static std::string compress(const std::string& str);
 
        // decompress data
        static std::string decompress(const std::string& str);

    };
}

#endif