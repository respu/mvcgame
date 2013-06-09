
#include <mvcgame/font/FntFontAtlasLoader.hpp>
#include <mvcgame/font/FontAtlas.hpp>

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
        return std::round(std::stof(itr->second));
    }

    template<>
    float FntFontAtlasData::getValue(const std::string& name, const float& def) const
    {
        Map::const_iterator itr = _values.find(name);
        if(itr == _values.end())
        {
            return def;
        }
        return std::stof(itr->second);
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
			if(p>=str.size())
			{
				break;
			}
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
                FontInfo& info = atlas->getInfo();
                info.name = data.getValue<std::string>("face", info.name);
                info.size = data.getValue<int>("size", info.size);
                info.bold = data.getValue<bool>("bold", info.bold);
                info.italic = data.getValue<bool>("italic", info.italic);

            }
            else if(data.getName() == "common")
            {
                FontInfo& info = atlas->getInfo();                
                info.lineHeight = data.getValue<int>("lineHeight", info.lineHeight);
                info.baseHeight = data.getValue<int>("base", info.baseHeight);
            }            
            else if(data.getName() == "page")
            {
                int i = data.getValue<int>("id", -1);
                if(i>=0)
                {
                    FontAtlasPage& page = atlas->getPage(i);
                    page.setTextureName(data.getValue<std::string>("file", page.getTextureName()));
                }
            }
            else if(data.getName() == "char")
            {
                FontRegion charTex;
                charTex.origin = TextureRegion::Origin::TopLeft;
                charTex.x = data.getValue<int>("x", charTex.x);
                charTex.y = data.getValue<int>("y", charTex.y);
                charTex.width = data.getValue<int>("width", charTex.width);
                charTex.height = data.getValue<int>("height", charTex.height);
                charTex.offsetX = data.getValue<int>("xoffset", charTex.offsetX);
                charTex.offsetY = data.getValue<int>("yoffset", charTex.offsetY);
                charTex.advanceX = data.getValue<float>("xadvance", charTex.advanceX);
                charTex.name = data.getValue<std::string>("letter", charTex.name);
                if(charTex.name == "space")
                {
                    charTex.name = " ";
                }
                unsigned page = data.getValue<int>("page", 0);
                charTex.originalWidth = charTex.width;
                charTex.originalHeight = charTex.height;
                atlas->getPage(page).addRegion(charTex);
            }
        }
        
        return atlas;
    }

}