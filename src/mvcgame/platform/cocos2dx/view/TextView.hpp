
#ifndef mvcgame_cocos2dx_TextView_hpp
#define mvcgame_cocos2dx_TextView_hpp

#include <mvcgame/view/BaseTextView.hpp>
#include <mvcgame/platform/cocos2dx/view/View.hpp>

namespace cocos2d {
    class CCLabelTTF;
    class CCLabelAtlas;
    class CCLabelIBMFont;
    class CCLabelProtocol;
}

namespace mvcgame {
  
    class TextView : public View, public BaseTextView
    {
    private:
        cocos2d::CCLabelTTF* _label;
    protected:
        void updateNodeFrame(cocos2d::CCNode* node);        
        void updateLabel(cocos2d::CCLabelTTF* label);
        void updateLabelHorizontalAlign(cocos2d::CCLabelTTF* label);
        void updateLabelVerticalAlign(cocos2d::CCLabelTTF* label);
        void updateLabelFont(cocos2d::CCLabelTTF* label);
        void updateLabelSize(cocos2d::CCLabelTTF* label);
        void updateLabelText(cocos2d::CCLabelTTF* label);
        void updateLabelColor(cocos2d::CCLabelTTF* label);
    public:
        TextView(cocos2d::CCLabelTTF* label);
        TextView();
        void setTextHorizontalAlign(ITextView::HorizontalAlign align);
        void setTextVerticalAlign(ITextView::VerticalAlign align);
        void setTextFont(const std::string& font);
        void setTextSize(unsigned short size);
        void setText(const std::string& text);
        void setTextColor(const Color& color);       
    };
    
}

#endif