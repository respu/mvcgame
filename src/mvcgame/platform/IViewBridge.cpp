
#include <mvcgame/platform/IViewBridge.hpp>
#include <mvcgame/texture/TextureRegion.hpp>

namespace mvcgame {

    void IViewBridge::drawTexture(const Rect& rect, const Texture& texture)
    {
        drawTexture(rect, texture, TextureRegion(texture));
    }
}