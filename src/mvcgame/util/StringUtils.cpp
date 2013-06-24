

#include <mvcgame/util/StringUtils.hpp>

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <stdexcept>

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

    /**
     * base64 code taken from
     * https://github.com/ReneNyffenegger/development_misc/blob/master/base64/base64.cpp
     */
    static const std::string base64Chars = 
                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                 "abcdefghijklmnopqrstuvwxyz"
                 "0123456789+/";   

    std::string StringUtils::base64Encode(const std::string& s)
    {
        std::string ret;
        int i = 0;
        int j = 0;
        unsigned char charArray3[3];
        unsigned char charArray4[4];

        for(const unsigned char& ch : s)
        {
            charArray3[i++] = ch;
            if (i == 3)
            {
                charArray4[0] = (charArray3[0] & 0xfc) >> 2;
                charArray4[1] = ((charArray3[0] & 0x03) << 4) + ((charArray3[1] & 0xf0) >> 4);
                charArray4[2] = ((charArray3[1] & 0x0f) << 2) + ((charArray3[2] & 0xc0) >> 6);
                charArray4[3] = charArray3[2] & 0x3f;

                for(i = 0; (i <4) ; i++)
                {
                    ret += base64Chars[charArray4[i]];
                }
                i = 0;
            }
        }

        if (i)
        {
            for(j = i; j < 3; j++)
            {
                charArray3[j] = '\0';
            }

            charArray4[0] = (charArray3[0] & 0xfc) >> 2;
            charArray4[1] = ((charArray3[0] & 0x03) << 4) + ((charArray3[1] & 0xf0) >> 4);
            charArray4[2] = ((charArray3[1] & 0x0f) << 2) + ((charArray3[2] & 0xc0) >> 6);
            charArray4[3] = charArray3[2] & 0x3f;

            for (j = 0; (j < i + 1); j++)
            {
                ret += base64Chars[charArray4[j]];
            }

            while((i++ < 3))
            {
                ret += '=';
            }
        }
        return ret;
    }

    static inline bool isBase64(unsigned char c)
    {
      return (isalnum(c) || (c == '+') || (c == '/'));
    }    

    std::string StringUtils::base64Decode(const std::string& s)
    {
        int inLen = s.size();
        int i = 0;
        int j = 0;
        int k = 0;
        unsigned char charArray4[4], charArray3[3];
        std::string ret;

        while (inLen-- && ( s[k] != '='))
        {
            if(!isBase64(s[k]))
            {
                throw new std::runtime_error("Invalid base64 char");
            }
            charArray4[i++] = s[k];
            k++;
            if (i ==4)
            {
                for (i = 0; i <4; i++)
                {
                    charArray4[i] = base64Chars.find(charArray4[i]);
                }

                charArray3[0] = (charArray4[0] << 2) + ((charArray4[1] & 0x30) >> 4);
                charArray3[1] = ((charArray4[1] & 0xf) << 4) + ((charArray4[2] & 0x3c) >> 2);
                charArray3[2] = ((charArray4[2] & 0x3) << 6) + charArray4[3];

                for (i = 0; (i < 3); i++)
                {
                    ret += charArray3[i];
                }
                i = 0;
            }
        }

        if (i)
        {
            for (j = i; j <4; j++)
            {
                charArray4[j] = 0;
            }

            for (j = 0; j <4; j++)
            {
                charArray4[j] = base64Chars.find(charArray4[j]);
            }

            charArray3[0] = (charArray4[0] << 2) + ((charArray4[1] & 0x30) >> 4);
            charArray3[1] = ((charArray4[1] & 0xf) << 4) + ((charArray4[2] & 0x3c) >> 2);
            charArray3[2] = ((charArray4[2] & 0x3) << 6) + charArray4[3];

            for (j = 0; (j < i - 1); j++)
            {
                ret += charArray3[j];
            }
        }

        return ret;
    }
}