//
//  View.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_View_hpp
#define mvcgame_View_hpp

#include <mvcgame/BaseView.hpp>
#include <mvcgame/Geometry.hpp>
#include <cocos2dx/base_nodes/CCNode.h>

namespace mvcgame {
  
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
        
        void addChild(IView* child, unsigned layer=0);
        void removeChild(IView* child);
    };
    
}

#endif