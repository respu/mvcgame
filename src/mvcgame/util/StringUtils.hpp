
#ifndef mvcgame_StringUtils_hpp
#define mvcgame_StringUtils_hpp

#include <string>
#include <vector>

namespace mvcgame {

    class StringUtils
    {
    public:

        static const std::string DefaultTrimValues;

        // trim from start
        static void ltrim(std::string& str, const std::string& chr=DefaultTrimValues);

        // trim from end
        static void rtrim(std::string& str, const std::string& chr=DefaultTrimValues); 

        // trim from both ends
        static void trim(std::string& str, const std::string& chr=DefaultTrimValues);

        // encode base64
        static std::string base64Encode(const std::string& s);

        // decode base64
        static std::string base64Decode(const std::string& s);

        // compress data
        static std::string compress(const std::string& str);
 
        // decompress data
        static std::string decompress(const std::string& str);

        // split a string
        static std::vector<std::string> split(const std::string &str, const char sep, size_t max=std::string::npos);
    };
}

#endif