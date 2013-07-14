
#include <mvcgame/physics/CocosPhysicsAtlasLoader.hpp>
#include <mvcgame/physics/PhysicsAtlas.hpp>
#include <mvcgame/util/StringUtils.hpp>
#include <rapidxml/rapidxml.hpp>

using namespace rapidxml;

namespace mvcgame {

    typedef std::vector<char> XmlBuffer;

    class CocosPhysicsAtlasLoaderBridge
    {
    private:

        void loadXmlDocument(rapidxml::xml_document<>& doc, std::istream& input, XmlBuffer& buffer)
        {
            buffer.assign((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
            buffer.push_back('\0');
            doc.parse<0>(&buffer[0]);
        }

    public:
        bool validate(std::istream& input)
        {
            xml_document<> doc;
            XmlBuffer buffer;
            loadXmlDocument(doc, input, buffer);
            return std::string(doc.first_node()->name()) == "plist";
        }

        std::shared_ptr<PhysicsAtlas> load(std::istream& input)
        {
            xml_document<> doc;
            XmlBuffer buffer;
            loadXmlDocument(doc, input, buffer);            
            return std::make_shared<PhysicsAtlas>();
        }
    };

    CocosPhysicsAtlasLoader::CocosPhysicsAtlasLoader() :
    _bridge(new CocosPhysicsAtlasLoaderBridge())
    {
    }

    CocosPhysicsAtlasLoader::~CocosPhysicsAtlasLoader()
    {
        delete _bridge;
    }

    bool CocosPhysicsAtlasLoader::validate(std::istream& input) const
    {
        return _bridge->validate(input);
    }

    std::shared_ptr<PhysicsAtlas> CocosPhysicsAtlasLoader::load(std::istream& input) const
    {
    	return _bridge->load(input);
    }

}