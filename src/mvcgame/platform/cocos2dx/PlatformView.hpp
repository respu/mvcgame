//
//  PlatformView.hpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef hydra_PlatformView_hpp
#define hydra_PlatformView_hpp

#include <mvcgame/View.hpp>
#include <mvcgame/Geometry.hpp>
#include "base_nodes/CCNode.h"

namespace mvcgame {
  
    class PlatformView : public View
    {
    private:
        IView::Children _children;
        cocos2d::CCNode* _node;

        void setNode(cocos2d::CCNode* node);
    public:
        PlatformView(cocos2d::CCNode* node);
        PlatformView();
        ~PlatformView();

        void setFrame(const Rect& rect);
        void setRotation(const Rotation& r);
        void setScale(const Scale& s);
        void setAnchor(const Anchor& a);
        
        void addChild(IView* child, unsigned layer=0);
        void removeChild(IView* child);
    };
    
}

#endif