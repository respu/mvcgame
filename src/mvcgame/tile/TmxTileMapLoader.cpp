
#include <mvcgame/tile/TmxTileMapLoader.hpp>
#include <mvcgame/tile/TileMap.hpp>
#include <mvcgame/util/StringUtils.hpp>
#include <mvcgame/asset/AssetStreamManager.hpp>
#include <mvcgame/asset/AssetManager.hpp>
#include <rapidxml/rapidxml.hpp>

#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace rapidxml;

namespace mvcgame {

    typedef std::vector<char> XmlBuffer;

    class TmxTileMapLoaderBridge
    {
    private:
        AssetStreamManager* _streamManager;
        AssetManager<Texture>* _textureManager;

        void loadXmlDocument(rapidxml::xml_document<>& doc, std::istream& input, XmlBuffer& buffer)
        {
            buffer.assign((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
            buffer.push_back('\0');
            doc.parse<0>(&buffer[0]);
        }

        bool loadExternalTileSet(std::istream& in, TileSet& tileSet)
        {
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
        }

        void loadTileSet(xml_node<>* node, TileSet& tileSet)
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
            attr = node->first_attribute("firstgid");
            if(attr)
            {
                tileSet.setFirstTypeId(std::stoi(attr->value()));
            }

            auto offsetNode = node->first_node("tileoffset");
            if(offsetNode)
            {
                attr = node->first_attribute("x");
                if(attr)
                {
                    tileSet.setTileOffsetX(std::stoi(attr->value()));
                }
                attr = node->first_attribute("y");
                if(attr)
                {
                    tileSet.setTileOffsetY(std::stoi(attr->value()));
                }                
            }

            auto imgNode = node->first_node("image");
            if(imgNode)
            {
                attr = imgNode->first_attribute("source");
                if(attr && _textureManager)
                {
                    tileSet.setTexture(_textureManager->load(attr->value()));
                }
            }

            attr = node->first_attribute("source");
            if(attr)
            {
                if(!_streamManager)
                {
                    throw new std::runtime_error("No source loader set");
                }
                std::string source = attr->value();
                bool result = _streamManager->load(source,
                    std::bind(&TmxTileMapLoaderBridge::loadExternalTileSet,
                        this, std::placeholders::_1, std::ref(tileSet)));
                if(!result)
                {
                    throw new std::runtime_error("Failed to load tileset source '" + source +"'");
                }
            }
        }

        void loadTileSets(xml_node<>* parentNode, TileMap::Sets& tileSets)
        {
            auto node = parentNode->first_node("tileset");
            while (node != nullptr)
            {
                tileSets.resize(tileSets.size()+1);
                loadTileSet(node, tileSets.back());
                node = node->next_sibling("tileset");
            }   
        }

        enum class DataType
        {
            Unknown,
            Binary,
            Csv
        };

        DataType loadData(xml_node<>* node, std::string& data)
        {
            auto attr = node->first_attribute("encoding");
            data = node->value();
            DataType type = DataType::Unknown;
            if(attr)
            {
                data.erase(std::remove_if(data.begin(), data.end(), std::ptr_fun<int, int>(std::isspace)), data.end());
                std::string enc = attr->value();  
                if(enc == "base64")
                {
                    data = StringUtils::base64Decode(data);
                    type = DataType::Binary;
                }
                else if(enc == "csv")
                {
                    type = DataType::Csv;
                }
                else
                {
                    throw std::runtime_error("Unknown data encoding '"+enc+"'");
                }
            }
            attr = node->first_attribute("compression");
            if(attr)
            {
                std::string comp = attr->value();
                if(comp == "zlib")
                {
                    data = StringUtils::decompress(data);              
                }
                else
                {
                    throw std::runtime_error("Unknown data compression '"+comp+"'");
                }
            }
            return type;
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
            if(dataNode)
            {
                std::string data;
                DataType type = loadData(dataNode, data);

                if(type == DataType::Binary)
                {
                    unsigned i = 0;
                    if(data.size() != 4*layer.getHeight()*layer.getWidth())
                    {
                        throw std::runtime_error("Incorrect layer data size");
                    }
                    for (unsigned y = 0; y < layer.getHeight(); ++y)
                    {
                        for (unsigned x = 0; x < layer.getWidth(); ++x)
                        {
                            unsigned typeId = data[i] | data[i + 1] << 8 | data[i + 2] << 16 | data[i + 3] << 24;
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
                else if(type == DataType::Csv)
                {
                    throw std::runtime_error("CSV tile layer data not implemented.");
                }
                else
                {
                    throw std::runtime_error("Unknown data type for TileLayer.");
                }
            }
        }    

        void loadTileLayers(xml_node<>* parentNode, TileMap::Layers& tileLayers)
        {
            auto node = parentNode->first_node("layer");
            while (node != nullptr)
            {
                tileLayers.resize(tileLayers.size()+1);
                loadTileLayer(node, tileLayers.back());            
                node = node->next_sibling("layer");
            }
        }  

    public:
        TmxTileMapLoaderBridge(AssetStreamManager* streamManager=nullptr, AssetManager<Texture>* textureManager=nullptr) :
        _streamManager(streamManager), _textureManager(textureManager)
        {
        }

        bool validate(std::istream& input)
        {
            xml_document<> doc;
            XmlBuffer buffer;
            loadXmlDocument(doc, input, buffer);
            return std::string(doc.first_node()->name()) == "map";
        }

        std::unique_ptr<TileMap> load(std::istream& input)
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

            loadTileSets(mapNode, map->getSets());
            loadTileLayers(mapNode, map->getLayers());
            
            return map;
        }
    };

    TmxTileMapLoader::TmxTileMapLoader() :
    _streamManager(nullptr), _textureManager(nullptr)
    {
    }

    void TmxTileMapLoader::setStreamManager(AssetStreamManager& mng)
    {
        _streamManager = &mng;
    }

    void TmxTileMapLoader::setTextureManager(AssetManager<Texture>& mng)
    {
        _textureManager = &mng;
    }

    bool TmxTileMapLoader::validate(std::istream& input) const
    {
        TmxTileMapLoaderBridge bridge(_streamManager, _textureManager);
        return bridge.validate(input);
    }
    
    std::unique_ptr<TileMap> TmxTileMapLoader::load(std::istream& input) const
    {
        TmxTileMapLoaderBridge bridge(_streamManager, _textureManager);
        return bridge.load(input);
    }

}