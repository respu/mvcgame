#include <mvcgame/platform/cocos2dx/view/ColorView.hpp>
#include <cocos2dx/layers_scenes_transitions_nodes/CCLayer.h>

namespace mvcgame {

    ColorView::ColorView(cocos2d::CCLayerColor* layer) : View(layer)
    {

    }

    ColorView::ColorView() : View(new cocos2d::CCLayerColor())
    {

    }

	void ColorView::setBackgroundColor(const Color& color)
	{
		BaseColorView::setBackgroundColor(color);
	}
}