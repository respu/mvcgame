  
#ifndef mvcgame_FontSheet_hpp
#define mvcgame_FontSheet_hpp

#include <mvcgame/font/FontInfo.hpp>
#include <mvcgame/font/FontLetter.hpp>

#include <string>
#include <map>

namespace mvcgame {

    class FontSheet
    {
    public:
        typedef FontInfo Info;
        typedef FontLetter Letter;
        typedef std::map<std::string,Letter> Letters;
    private:
        Info _info;
        Letters _letters;
    public:
        FontSheet();

        const Info& getInfo() const;
        Info& getInfo();
        void setInfo(const Info& info);

        const Letters& getLetters() const;
        Letters& getLetters();
        
        bool hasLetter(const std::string& name) const;
        const Letter& getLetter(const std::string& name) const;
        Letter& getLetter(const std::string& name);
        void setLetter(const std::string& name, Letter letter);

        SpriteFrame getSpriteFrame(const Letter& letter) const;
    };
}

#endif