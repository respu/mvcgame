

#ifndef mvcgame_IStreamLoader_hpp
#define mvcgame_IStreamLoader_hpp

#include <string>
#include <functional>

namespace mvcgame {

    class IStreamLoader
    {
    public:

        /**
         * Called by the loader with each possible stream
         * @return true if the stream was loaded correctly
         */
        typedef std::function<bool(std::istream& in)> Callback;

        virtual ~IStreamLoader(){};

        /**
         * @return true if the asset can be loaded
         */
        virtual bool validate(const std::string& name) const
        {
            return true;
        }

        /**
         * should try to load possible streams using the callback
         */
        virtual bool load(const std::string& name, Callback callback) = 0;
    };

}

#endif