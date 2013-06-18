
#include <mvcgame/tile/TmxTileMapLoader.hpp>
#include <mvcgame/tile/TileMap.hpp>

#include <vector>
#include <rapidxml/rapidxml.hpp>

namespace mvcgame {

    void loadXmlDocument(rapidxml::xml_document<>& doc, std::istream& input)
    {
        std::vector<char> buffer((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
        buffer.push_back('\0');
        doc.parse<0>(&buffer[0]);
    }

    bool TmxTileMapLoader::validate(std::istream& input) const
    {
        rapidxml::xml_document<> doc;
        loadXmlDocument(doc, input);
        return std::string(doc.first_node()->name()) == "map";
    }

    std::unique_ptr<TileMap> TmxTileMapLoader::load(std::istream& input) const
    {
        std::unique_ptr<TileMap> map(new TileMap());
        rapidxml::xml_document<> doc;
        loadXmlDocument(doc, input);
        return map;
    }

}