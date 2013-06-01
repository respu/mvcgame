

#ifndef mvcgame_IAssetLoader_hpp
#define mvcgame_IAssetLoader_hpp

#include <memory>
#include <iostream>

namespace mvcgame {

    template<typename Asset>
    class IAssetLoader
    {
    public:
        virtual ~IAssetLoader(){};

        /**
         * should return an unique tag to identify assets if this type
         */
        virtual const std::string& getTag() const = 0;

        /**
         * The stream should be at the start
         * @return true if the asset can be loaded
         */
        virtual bool validate(std::istream& input)
        {
            return true;
        }

        /**
         * The stream should be at the start
         * @return the new asset
         */
        virtual std::unique_ptr<Asset> load(std::istream& input) = 0;
    };

}

#endif