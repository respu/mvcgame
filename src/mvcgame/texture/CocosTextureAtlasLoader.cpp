
#include <mvcgame/texture/CocosTextureAtlasLoader.hpp>
#include <mvcgame/texture/TextureAtlas.hpp>
#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/asset/AssetManager.hpp>
#include <mvcgame/util/StringUtils.hpp>
#include <rapidxml/rapidxml.hpp>

#include <cassert>
#include <string>
#include <stdexcept>

using namespace rapidxml;

namespace mvcgame {

    typedef std::vector<char> XmlBuffer;

    class CocosTextureAtlasLoaderBridge
    {
    private:
        AssetManager<Texture>* _textureManager;

        void loadXmlDocument(rapidxml::xml_document<>& doc, std::istream& input, XmlBuffer& buffer)
        {
            buffer.assign((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
            buffer.push_back('\0');
            doc.parse<0>(&buffer[0]);
        }
    public:
        CocosTextureAtlasLoaderBridge(AssetManager<Texture>* textureManager=nullptr) :
        _textureManager(textureManager)
        {
        }

        bool validate(std::istream& input)
        {
            xml_document<> doc;
            XmlBuffer buffer;
            loadXmlDocument(doc, input, buffer);
            return std::string(doc.first_node()->name()) == "plist";
        }

        std::vector<int> loadIntegerParts(const std::string& value)
        {
            std::vector<std::string> strparts = StringUtils::split(value, ',');
            std::vector<int> parts;
            for(std::string& strpart : strparts)
            {
                StringUtils::trim(strpart, "{}");
                parts.push_back(std::stoi(strpart));
            }
            return parts;
        }

        void loadFrame(xml_node<>* dict, TextureRegion& region)
        {
            auto key = dict->first_node("key");
            while(key != nullptr)
            {
                std::string name = key->value();
                if(name == "frame")
                {
                    std::string value = key->next_sibling()->value();
                    std::vector<int> parts = loadIntegerParts(value);
                    if(parts.size() != 4)
                    {
                        throw std::runtime_error("Invalid frame value.");
                    }
                    region.x = parts[0];
                    region.y = parts[1];
                    region.width = parts[2];
                    region.height = parts[3];

                }
                else if(name == "offset")
                {
                    std::string value = key->next_sibling()->value();
                    std::vector<int> parts = loadIntegerParts(value);
                    if(parts.size() != 2)
                    {
                        throw std::runtime_error("Invalid offset value.");
                    }
                    region.offsetX = parts[0];
                    region.offsetY = parts[1];                    
                }
                else if(name == "rotated")
                {                
                    std::string value = key->next_sibling()->name();
                    region.rotate = value == "true";
                }
                else if(name == "sourceSize")                
                {
                    std::string value = key->next_sibling()->value();
                    std::vector<int> parts = loadIntegerParts(value);
                    if(parts.size() != 2)
                    {
                        throw std::runtime_error("Invalid sourceSize value.");
                    }
                    region.originalWidth = parts[0];
                    region.originalHeight = parts[1];  
                }
                key = key->next_sibling("key");
            }
        }

        void loadFrames(xml_node<>* dict, TextureAtlas& atlas)
        {
            auto key = dict->first_node("key");
            while(key != nullptr)
            {
                TextureRegion region;
                region.origin = TextureRegion::Origin::TopLeft;
                region.name = key->value();
                loadFrame(key->next_sibling("dict"), region);
                atlas.addRegion(region);
                key = key->next_sibling("key");
            }
        }

        void loadMetadata(xml_node<>* dict, TextureAtlas& atlas)
        {
            auto key = dict->first_node("key");
            while(key != nullptr)
            {
                std::string name = key->value();
                if(name == "textureFileName")
                {
                    auto value = key->next_sibling();
                    atlas.setTexture(_textureManager->load(value->value()));
                }
                key = key->next_sibling("key");
            }
        }

        std::shared_ptr<TextureAtlas> load(std::istream& input)
        {
            xml_document<> doc;
            XmlBuffer buffer;
            loadXmlDocument(doc, input, buffer);
            
            auto atlas = std::make_shared<TextureAtlas>();
            auto root = doc.first_node("plist");
            auto dict = root->first_node("dict");
            while (dict != nullptr)
            {
                auto key = dict->first_node("key");
                while(key != nullptr)
                {
                    std::string name = key->value();
                    if(name == "frames")
                    {
                        loadFrames(key->next_sibling("dict"), *atlas);
                    }
                    if(name == "metadata")
                    {
                        loadMetadata(key->next_sibling("dict"), *atlas);
                    }
                    key = key->next_sibling("key");
                }
                dict = dict->next_sibling("dict");
            }
            return atlas;
        }
    };

    CocosTextureAtlasLoader::CocosTextureAtlasLoader() :
    _textureManager(nullptr)
    {
    }
    
    bool CocosTextureAtlasLoader::validate(std::istream& input) const
    {
        CocosTextureAtlasLoaderBridge bridge(_textureManager);
        return bridge.validate(input);
    }

    std::shared_ptr<TextureAtlas> CocosTextureAtlasLoader::load(std::istream& input) const
    {
        CocosTextureAtlasLoaderBridge bridge(_textureManager);
        return bridge.load(input);
    }

    void CocosTextureAtlasLoader::setTextureManager(AssetManager<Texture>& mng)
    {
        _textureManager = &mng;
    }

}