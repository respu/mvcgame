

#include <mvcgame/util/StringUtils.hpp>

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

namespace mvcgame {

    void StringUtils::ltrim(std::string &s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    }

    void StringUtils::rtrim(std::string &s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    }

    void StringUtils::trim(std::string &s)
    {
        ltrim(s);
        rtrim(s);
    }

    static const std::string base64_chars = 
                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                 "abcdefghijklmnopqrstuvwxyz"
                 "0123456789+/";


    static inline bool is_base64(unsigned char c) {
      return (isalnum(c) || (c == '+') || (c == '/'));
    }    

    void StringUtils::base64Encode(std::string& s)
    {

    }

    void StringUtils::base64Decode(std::string& s)
    {

    }
}