
#include <mvcgame/texture/FntFontAtlasLoader.hpp>
#include <mvcgame/texture/FontAtlas.hpp>

#include <string>
#include <algorithm>

#define ATTR_SEP ' '
#define ATTR_VAL_SEP '='
#define ATTR_GROUP '"'

namespace mvcgame {

    const std::string& FntFontAtlasData::getName() const
    {
        return _name;
    }

    void FntFontAtlasData::setName(const std::string& name)
    {
        _name = name;
    }

    void FntFontAtlasData::setValue(const std::string& name, const std::string& value)
    {
        _values[name] = value;
    }
    
    template<>
    std::string FntFontAtlasData::getValue(const std::string& name, const std::string& def) const
    {
        Map::const_iterator itr = _values.find(name);
        if(itr == _values.end())
        {
            return def;
        }
        return itr->second;
    }

    template<>
    int FntFontAtlasData::getValue(const std::string& name, const int& def) const
    {
        Map::const_iterator itr = _values.find(name);
        if(itr == _values.end())
        {
            return def;
        }
        return stoi(itr->second);
    }

    template<>
    float FntFontAtlasData::getValue(const std::string& name, const float& def) const
    {
        Map::const_iterator itr = _values.find(name);
        if(itr == _values.end())
        {
            return def;
        }
        return stof(itr->second);
    }    

    template<>
    bool FntFontAtlasData::getValue(const std::string& name, const bool& def) const
    {
        Map::const_iterator itr = _values.find(name);
        if(itr == _values.end())
        {
            return def;
        }
        return itr->second == "1";
    }    

    bool FntFontAtlasLoader::validate(std::istream& in) const
    {
        std::string line;
        std::getline(in, line);
        return line.find("info ") == 0;
    }

    FntFontAtlasLoader::Data FntFontAtlasLoader::parseData(const std::string& str)
    {
        std::size_t p = str.find(ATTR_SEP);
        Data data;
        data.setName(str.substr(0, p));

        while(true)
        {
            if(str[p] == ATTR_SEP)
            {
                p++;
                continue;
            }
            std::size_t n = str.find(ATTR_SEP, p);
            if(n == std::string::npos)
            {
                n = str.size()-1;
            }
            std::size_t s = str.find(ATTR_VAL_SEP, p);
            if(s == std::string::npos)
            {
                break;
            }            
            std::string name = str.substr(p, s-p);
            s++;
            if(str[s] == ATTR_GROUP)
            {
                s++;
                n = str.find(ATTR_GROUP, s);
                if(n == std::string::npos)
                {
                    break;
                }
            }
            std::string value = str.substr(s, n-s);
            data.setValue(name, value);
            p = n;
        }
        return data;
    }

    std::unique_ptr<FontAtlas> FntFontAtlasLoader::load(std::istream& in) const
    {
        std::unique_ptr<FontAtlas> atlas(new FontAtlas());

        std::string str;

        while(in)
        {
            std::getline(in, str);
            Data data = parseData(str);
            if(data.getName() == "info")
            {
                atlas->setName(data.getValue<std::string>("face", atlas->getName()));
                atlas->setSize(data.getValue<int>("size", atlas->getSize()));
                atlas->setBold(data.getValue<bool>("bold", atlas->getBold()));
                atlas->setItalic(data.getValue<bool>("italic", atlas->getItalic()));
            }
            else if(data.getName() == "page")
            {
                
            }
            else if(data.getName() == "char")
            {
                TextureRegion charTex;
                charTex.x = data.getValue<float>("x", charTex.x);
                charTex.y = data.getValue<float>("y", charTex.y);
                charTex.width = data.getValue<float>("width", charTex.width);
                charTex.height = data.getValue<float>("height", charTex.height);
                charTex.offsetX = data.getValue<float>("xoffset", charTex.offsetX);
                charTex.offsetY = data.getValue<float>("yoffset", charTex.offsetY);
                charTex.name = data.getValue<std::string>("letter", charTex.name);
                unsigned page = data.getValue<int>("page", 0);
                atlas->getPage(page).addRegion(charTex);
            }
        }

/*
info face="font" size=32 bold=0 italic=0 charset="" unicode=0 stretchH=50 smooth=1 aa=1 padding=0,0,0,0 spacing=0,0
common lineHeight=37 base=30.5 scaleW=512 scaleH=256 pages=1 packed=0
page id=0 file="CurseCasualDF.png"
chars count=83
char id=32     x=470.5   y=161.5   width=0     height=0     xoffset=0     yoffset=30.5    xadvance=5.5    page=0 chnl=0 letter="space"
*/

        return atlas;
    }

}