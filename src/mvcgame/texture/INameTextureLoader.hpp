

#ifndef mvcgame_INameTextureLoader_hpp
#define mvcgame_INameTextureLoader_hpp

#include <memory>
#include <string>

namespace mvcgame {

    class Texture;
    class AssetsManager;

    class INameTextureLoader
    {
    public:
        virtual ~INameTextureLoader(){};

        /**
         * The stream should be at the start
         * @return true if the texture can be loaded
         */
        virtual bool validate(const std::string& name)
        {
            return true;
        }

        /**
         * The stream should be at the start
         * @return the new texture
         */
        virtual std::unique_ptr<Texture> load(const std::string& name) = 0;
    };

}

#endif