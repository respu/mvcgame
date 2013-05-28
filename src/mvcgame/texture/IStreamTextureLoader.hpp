

#ifndef mvcgame_IStreamTextureLoader_hpp
#define mvcgame_IStreamTextureLoader_hpp

#include <memory>
#include <iostream>
#include <fstream>

namespace mvcgame {

    class Texture;

    class IStreamTextureLoader
    {
    public:
        virtual ~IStreamTextureLoader(){};

        /**
         * The stream should be at the start
         * @return true if the texture can be loaded
         */
        virtual bool validate(std::istream& input)
        {
            return true;
        }

        /**
         * The stream should be at the start
         * @return the new texture
         */
        virtual std::unique_ptr<Texture> load(std::istream& input) = 0;
    };

}

#endif