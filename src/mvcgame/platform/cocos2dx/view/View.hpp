//
//  View.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_cocos2dx_View_hpp
#define mvcgame_cocos2dx_View_hpp

#include <mvcgame/view/BaseView.hpp>

namespace cocos2d {
    class CCNode;
}

namespace mvcgame {

    class View;
    typedef std::unique_ptr<View> ViewPtr;
  
    class View : public BaseView
    {
    private:
        IView::Children _children;
        cocos2d::CCNode* _node;

        void setNode(cocos2d::CCNode* node);
    public:
        View(cocos2d::CCNode* node);
        View();
        ~View();

        void setFrame(const Rect& rect);
        void setRotation(const Rotation& r);
        void setScale(const Scale& s);
        void setAnchor(const Anchor& a);
        
        void addChild(IViewPtr child, unsigned layer=0);
        void removeChild(const IView& child);
        void setParent(IView& parent);

        void addChild(ViewPtr child, unsigned layer=0);
        void removeChild(const View& child);
        void setParent(View& parent);        
    };
    
}

#endif