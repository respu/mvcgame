
#ifndef mvcgame_ITexture_hpp
#define mvcgame_ITexture_hpp

namespace mvcgame {

    class Size;
    
    /**
     * Represents a texture
     */
    class ITexture
    {
    public:
        virtual ~ITexture(){};
        virtual const Size& getSize() const = 0;
    };
}

#endif
