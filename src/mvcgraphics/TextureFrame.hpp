//
//  TextureFrame.hpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef __hydra__TextureFrame__
#define __hydra__TextureFrame__

#include <mvcgraphics/Geometry.hpp>
#include <mvcgraphics/ITexture.hpp>

namespace mvcgraphics {

    class TextureFrame : public ITexture
    {
    private:
        const ITexture& _texture;
        Rect _frame;
    public:
        TextureFrame(const ITexture& texture);
        TextureFrame(const ITexture& texture, const Rect& frame);
        const ITexture& getTexture() const;
        const Rect& getFrame() const;
        const Size& getSize() const;
    };
}

#endif
