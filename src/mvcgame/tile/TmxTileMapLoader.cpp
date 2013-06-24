
#include <mvcgame/tile/TmxTileMapLoader.hpp>
#include <mvcgame/tile/TileMap.hpp>
#include <mvcgame/asset/BaseAssetsManager.hpp>
#include <mvcgame/util/StringUtils.hpp>

#include <rapidxml/rapidxml.hpp>

#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace rapidxml;

namespace mvcgame {

    typedef std::vector<char> XmlBuffer;

    void loadXmlDocument(rapidxml::xml_document<>& doc, std::istream& input, XmlBuffer& buffer)
    {
        buffer.assign((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
        buffer.push_back('\0');
        doc.parse<0>(&buffer[0]);
    }

    TmxTileMapLoader::TmxTileMapLoader() :
    _sourceLoader(nullptr)
    {
    }

    void TmxTileMapLoader::setSourceLoader(BaseAssetsManager& loader)
    {
        _sourceLoader = &loader;
    }

    bool TmxTileMapLoader::validate(std::istream& input) const
    {
        xml_document<> doc;
        XmlBuffer buffer;
        loadXmlDocument(doc, input, buffer);
        return std::string(doc.first_node()->name()) == "map";
    }

    void loadTileSet(xml_node<>* node, TileSet& tileSet, BaseAssetsManager* sourceLoader=nullptr)
    {
        auto attr = node->first_attribute("name");
        if(attr)
        {
            tileSet.setName(attr->value());
        }
        attr = node->first_attribute("tilewidth");
        if(attr)
        {
            tileSet.setTileWidth(std::stoi(attr->value()));
        }
        attr = node->first_attribute("tileheight");
        if(attr)
        {
            tileSet.setTileHeight(std::stoi(attr->value()));
        }

        attr = node->first_attribute("source");
        if(attr)
        {
            if(!sourceLoader)
            {
                throw new std::runtime_error("No source loader set");
            }
            std::string source = attr->value();
            bool result = sourceLoader->loadStream(source, [&tileSet](std::istream& in, const std::string& tag){
                xml_document<> doc;
                XmlBuffer buffer;
                loadXmlDocument(doc, in, buffer);
                auto rootNode = doc.first_node();
                if(std::string(rootNode->name()) != "tileset")
                {
                    return false;
                }
                loadTileSet(rootNode, tileSet);
                return true;
            });
            if(!result)
            {
                throw new std::runtime_error("Failed to load tileset source '" + source +"'");
            }
        }
    }

    void loadTileSets(xml_node<>* parentNode, TileMap::Sets& tileSets, BaseAssetsManager* sourceLoader)
    {
        auto node = parentNode->first_node("tileset");
        while (node != nullptr)
        {
            tileSets.resize(tileSets.size()+1);
            loadTileSet(node, tileSets.back(), sourceLoader);
            node = node->next_sibling("tileset");
        }   
    }

    const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
    const unsigned FLIPPED_VERTICALLY_FLAG   = 0x40000000;
    const unsigned FLIPPED_DIAGONALLY_FLAG   = 0x20000000;    

    void loadTileLayer(xml_node<>* node, TileLayer& layer)
    {
        auto attr = node->first_attribute("name");
        if(attr)
        {
            layer.setName(attr->value());
        }
        attr = node->first_attribute("width");
        if(attr)
        {
            layer.setWidth(std::stoi(attr->value()));
        }
        attr = node->first_attribute("height");
        if(attr)
        {
            layer.setHeight(std::stoi(attr->value()));
        }
        auto dataNode = node->first_node("data");      
        if(!dataNode)
        {
            return;
        }        
        attr = dataNode->first_attribute("encoding");
        std::string val = dataNode->value(); 
        bool binary = false;       
        if(attr)
        {
            val.erase(std::remove_if(val.begin(), val.end(), std::ptr_fun<int, int>(std::isspace)), val.end());
            std::string enc = attr->value();  
            if(enc == "base64")
            {
                val = StringUtils::base64Decode(val);
                binary = true;
            }
            else
            {
                throw std::runtime_error("Unknown data encoding '"+enc+"'");
            }
        }
        attr = dataNode->first_attribute("compression");
        if(attr)
        {
            std::string comp = attr->value();
            if(comp == "zlib")
            {
                val = StringUtils::decompress(val);
                binary = true;                
            }
            else
            {
                throw std::runtime_error("Unknown data compression '"+comp+"'");
            }
        }
        if(binary)
        {
            unsigned i = 0;
            if(val.size() != 4*layer.getHeight()*layer.getWidth())
            {
                throw std::runtime_error("Incorrect layer data size");
            }
            for (unsigned y = 0; y < layer.getHeight(); ++y)
            {
                for (unsigned x = 0; x < layer.getWidth(); ++x)
                {
                    unsigned typeId = val[i] | val[i + 1] << 8 | val[i + 2] << 16 | val[i + 3] << 24;
                    i += 4;
                    Tile::Flip flip = Tile::Flip::None;
                    if(typeId & FLIPPED_HORIZONTALLY_FLAG)
                    {
                        flip = Tile::Flip::Horizontal;
                    }
                    else if(typeId & FLIPPED_VERTICALLY_FLAG)
                    {
                        flip = Tile::Flip::Vertical;   
                    }
                    else if(typeId & FLIPPED_DIAGONALLY_FLAG)
                    {
                        flip = Tile::Flip::Diagonal;   
                    }
                    typeId &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
                    layer.setTile(x, y, Tile(typeId, flip));
                }
            }
        }
    }    

    void loadTileLayers(xml_node<>* parentNode, TileMap::Layers& tileLayers)
    {
        auto node = parentNode->first_node("layer");
        std::cout << "lalala" << node << std::endl;
        while (node != nullptr)
        {
            tileLayers.resize(tileLayers.size()+1);
            loadTileLayer(node, tileLayers.back());            
            node = node->next_sibling("layer");
        }
    }  

    std::unique_ptr<TileMap> TmxTileMapLoader::load(std::istream& input) const
    {
        xml_document<> doc;
        XmlBuffer buffer;
        loadXmlDocument(doc, input, buffer);

        auto mapNode = doc.first_node("map");
        
        std::unique_ptr<TileMap> map(new TileMap(
            std::stoi(mapNode->first_attribute("width")->value()),
            std::stoi(mapNode->first_attribute("height")->value()),
            std::stoi(mapNode->first_attribute("tilewidth")->value()),
            std::stoi(mapNode->first_attribute("tileheight")->value())
        ));

        loadTileSets(mapNode, map->getSets(), _sourceLoader);
        loadTileLayers(mapNode, map->getLayers());
        
        return map;
    }

}