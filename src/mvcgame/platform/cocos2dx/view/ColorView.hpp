
#ifndef mvcgame_cocos2dx_ColorView_hpp
#define mvcgame_cocos2dx_ColorView_hpp

#include <mvcgame/view/BaseColorView.hpp>
#include <mvcgame/platform/cocos2dx/view/View.hpp>

namespace cocos2d {
    class CCLayerColor;
}

namespace mvcgame {
  
    class ColorView : public View, public BaseColorView
    {
    private:
    	cocos2d::CCLayerColor* _layer;
    public:
        ColorView(cocos2d::CCLayerColor* layer);
        ColorView();
        void setBackgroundColor(const Color& color);
    };
    
}

#endif