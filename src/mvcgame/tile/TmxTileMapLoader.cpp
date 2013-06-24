
#include <mvcgame/tile/TmxTileMapLoader.hpp>
#include <mvcgame/tile/TileMap.hpp>
#include <mvcgame/asset/BaseAssetsManager.hpp>

#include <rapidxml/rapidxml.hpp>

#include <vector>
#include <stdexcept>

using namespace rapidxml;

namespace mvcgame {

    void loadXmlDocument(rapidxml::xml_document<>& doc, std::istream& input)
    {
        std::vector<char> buffer((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
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
        loadXmlDocument(doc, input);
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
                loadXmlDocument(doc, in);
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
        while (node != nullptr )
        {
            tileSets.resize(tileSets.size()+1);
            loadTileSet(node, tileSets.back(), sourceLoader);
            node = node->next_sibling("tileset");
        }   
    }

    void loadTileLayer(xml_node<>* node, TileLayer& layer)
    {
        auto attr = node->first_attribute("name");
        if(attr)
        {
            layer.setName(attr->value());
        }
    }    

    void loadTileLayers(xml_node<>* parentNode, TileMap::Layers& tileLayers)
    {
        auto node = parentNode->first_node("layer");
        while (node != nullptr )
        {
            tileLayers.resize(tileLayers.size()+1);
            loadTileLayer(node, tileLayers.back());            
            node = node->next_sibling("layer");
        }
    }  

    std::unique_ptr<TileMap> TmxTileMapLoader::load(std::istream& input) const
    {
        xml_document<> doc;
        loadXmlDocument(doc, input);

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