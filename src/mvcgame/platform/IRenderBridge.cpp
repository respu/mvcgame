
#include <mvcgame/platform/IRenderBridge.hpp>
#include <mvcgame/texture/TextureRegion.hpp>

namespace mvcgame {

    void IRenderBridge::drawTexture(const Rect& rect, const Texture& texture)
    {
        drawTexture(rect, texture, TextureRegion(texture));
    }
}