

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

}