#include <mvcgame/platform/cocos2dx/view/ColorView.hpp>
#include <mvcgame/view/Color.hpp>

#include <cocos2dx/layers_scenes_transitions_nodes/CCLayer.h>

namespace mvcgame {

    ColorView::ColorView(cocos2d::CCLayerColor* layer) : View(layer), _layer(layer)
    {

    }

    ColorView::ColorView() : ColorView(new cocos2d::CCLayerColor())
    {
        assert(_layer->init());
    }

	void ColorView::setBackgroundColor(const Color& color)
	{
        _layer->initWithColor(cocos2d::ccc4(color.r,color.g,color.b,color.a));
		BaseColorView::setBackgroundColor(color);
	}
}