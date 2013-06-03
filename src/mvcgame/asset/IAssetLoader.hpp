

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
         * The stream should be at the start
         *
         * @return true if the asset can be loaded
         */
        virtual bool validate(std::istream& input) const
        {
            return true;
        }

        /**
         * The stream should be at the start
         * @return the new asset
         */
        virtual std::unique_ptr<Asset> load(std::istream& input) const= 0;
    };

}

#endif