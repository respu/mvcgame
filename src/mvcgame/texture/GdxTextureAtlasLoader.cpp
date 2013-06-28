
#include <mvcgame/texture/GdxTextureAtlasLoader.hpp>
#include <mvcgame/texture/TextureAtlas.hpp>
#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/asset/AssetManager.hpp>
#include <mvcgame/util/StringUtils.hpp>

#include <cassert>
#include <string>

namespace mvcgame {

    GdxTextureAtlasLoader::GdxTextureAtlasLoader() :
    _textureManager(nullptr)
    {
    }
    
    bool GdxTextureAtlasLoader::validate(std::istream& input) const
    {
        return true;
    }

    std::unique_ptr<TextureAtlas> GdxTextureAtlasLoader::load(std::istream& in) const
    {
        assert(_textureManager);

        std::unique_ptr<TextureAtlas> atlas(new TextureAtlas());
        std::string line;

        // texture name
        std::getline(in, line);
        if(_textureManager)
        {
            atlas->setTexture(_textureManager->load(line));
        }

        bool inRegion = false;
        TextureRegion region;

        while(in)
        {
            std::getline(in, line);
            std::size_t sep = line.find(':');
            std::string n = line.substr(0, sep);
            std::string v = line.substr(sep+1);

            if(!inRegion)
            {
                if(sep == std::string::npos)
                {
                    inRegion = true;
                    region = TextureRegion();
                    region.name = line;
                }
                else
                {
                    // header value
                }
            }
            else
            {
                if(line.substr(0, 1) == " ")
                {
                    StringUtils::trim(n);
                    StringUtils::trim(v);
                    if(n == "rotate")
                    {
                        region.rotate = v == "true";
                    }
                    else if(n == "xy")
                    {
                        sep = v.find(',');                       
                        region.x = std::stoi(v.substr(0, sep));
                        region.y = std::stoi(v.substr(sep+1));
                    }
                    else if(n == "size")
                    {
                        sep = v.find(',');
                        region.width = std::stoi(v.substr(0, sep));
                        region.height = std::stoi(v.substr(sep+1));
                    }
                    else if(n == "orig")
                    {
                        sep = v.find(',');
                        region.originalWidth = std::stoi(v.substr(0, sep));
                        region.originalHeight = std::stoi(v.substr(sep+1));
                    }
                    else if(n == "offset")
                    {
                        sep = v.find(',');
                        region.offsetX = std::stoi(v.substr(0, sep));
                        region.offsetY = std::stoi(v.substr(sep+1));
                    }
                    else if(n == "index")
                    {
                        region.index = std::stoi(v);
                    }
                }
                else
                {
                    region.origin = TextureRegion::Origin::TopLeft;
                    atlas->addRegion(region);
                    region = TextureRegion();
                    region.name = line;
                }             
            }
        }

        return std::move(atlas);
    }

    void GdxTextureAtlasLoader::setTextureManager(AssetManager<Texture>& mng)
    {
        _textureManager = &mng;
    }

}