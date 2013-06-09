
#ifndef mvcgame_FntFontAtlasLoader_hpp
#define mvcgame_FntFontAtlasLoader_hpp

#include <mvcgame/asset/IAssetLoader.hpp>
#include <map>

namespace mvcgame {

    class FontAtlas;

    class FntFontAtlasData final
    {
    private:
        typedef std::map<std::string, std::string> Map;
        std::string _name;
        Map _values;
    public:

        const std::string& getName() const;
        void setName(const std::string& name);

        void setValue(const std::string& name, const std::string& value);
        template<typename Type>
        Type getValue(const std::string& name, const Type& def) const;
    };

    class FntFontAtlasLoader : public IAssetLoader<FontAtlas>
    {
    private:
        typedef FntFontAtlasData Data;
        static Data parseData(const std::string& line);
    public:
        bool validate(std::istream& input) const;
        std::unique_ptr<FontAtlas> load(std::istream& input) const;
    };
}

#endif