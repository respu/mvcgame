

#include <mvcgame/util/StringUtils.hpp>

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <stdexcept>
#include <cstring>
#include <sstream>

#include <zlib.h>

namespace mvcgame {

    const std::string StringUtils::DefaultTrimValues = "\t\n\r ";

    void StringUtils::ltrim(std::string& str, const std::string& chrs)
    {
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), [&chrs](const char chr){
            return chrs.find(chr) == std::string::npos;
        }));
    }
    
    void StringUtils::rtrim(std::string& str, const std::string& chrs)
    {
        str.erase(std::find_if(str.rbegin(), str.rend(), [&chrs](const char chr){
            return chrs.find(chr) == std::string::npos;
        }).base(), str.end());
    }
    
    void StringUtils::trim(std::string& str, const std::string& chrs)
    {
        ltrim(str, chrs);
        rtrim(str, chrs);
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
                std::ostringstream oss;
                oss << "Invalid base64 char: '" << s[k];
                oss << "' at position " << k;
                throw std::runtime_error(oss.str());
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

    /**
     * Compression routines taken from
     * http://panthema.net/2007/0328-ZLibString.html
     */

    std::string StringUtils::compress(const std::string& str)
    {
        int compressionlevel = Z_BEST_COMPRESSION;
        z_stream zs;
        memset(&zs, 0, sizeof(zs));

        if (deflateInit(&zs, compressionlevel) != Z_OK)
        {
            throw std::runtime_error("deflateInit failed while compressing.");
        }

        zs.next_in = (Bytef*)str.data();
        zs.avail_in = str.size();

        int ret;
        char outbuffer[32768];
        std::string outstring;

        do
        {
            zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
            zs.avail_out = sizeof(outbuffer);

            ret = deflate(&zs, Z_FINISH);

            if (outstring.size() < zs.total_out)
            {
                // append the block to the output string
                outstring.append(outbuffer, zs.total_out - outstring.size());
            }
        } while (ret == Z_OK);

        deflateEnd(&zs);

        if (ret != Z_STREAM_END)
        {        
            // an error occurred that was not EOF
            std::ostringstream oss;
            oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
            throw std::runtime_error(oss.str());
        }

        return outstring;
    }

    std::string StringUtils::decompress(const std::string& str)
    {
        z_stream zs;
        memset(&zs, 0, sizeof(zs));

        if (inflateInit(&zs) != Z_OK)
        {
            throw std::runtime_error("inflateInit failed while decompressing.");
        }

        zs.next_in = (Bytef*)str.data();
        zs.avail_in = str.size();

        int ret;
        char outbuffer[32768];
        std::string outstring;

        do {
            zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
            zs.avail_out = sizeof(outbuffer);

            ret = inflate(&zs, 0);

            if (outstring.size() < zs.total_out)
            {
                outstring.append(outbuffer, zs.total_out - outstring.size());
            }

        } while (ret == Z_OK);

        inflateEnd(&zs);

        if (ret != Z_STREAM_END)
        {   
            // an error occurred that was not EOF
            std::ostringstream oss;
            oss << "Exception during zlib decompression: (" << ret << ") "
                << zs.msg;
            throw(std::runtime_error(oss.str()));
        }

        return outstring;
    }

    std::vector<std::string> StringUtils::split(const std::string &str, const char sep, size_t max)
    {
        std::vector<std::string> tokens;
        std::string token;
        for(char c : str)
        {
            if(c == sep && (max == std::string::npos || tokens.size()<max-1))
            {
                tokens.push_back(token);
                token = "";
            }
            else
            {
                token += c;
            }
        }
        if(!token.empty())
        {
            tokens.push_back(token);
        }
        return tokens;
    }    
}