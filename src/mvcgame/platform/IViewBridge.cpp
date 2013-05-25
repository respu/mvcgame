
#include <mvcgame/platform/IViewBridge.hpp>
#include <mvcgame/texture/Texture.hpp>

namespace mvcgame {

    void IViewBridge::drawTexture(const Rect& rect, const Texture& texture)
    {
        drawTexture(rect, texture, texture.getSize());
    }
}