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
    protected:
        cocos2d::CCNode* _node;

        virtual void updateNode(cocos2d::CCNode* node);        
        virtual void updateNodeFrame(cocos2d::CCNode* node);
        virtual void updateNodeRotation(cocos2d::CCNode* node);
        virtual void updateNodeAnchor(cocos2d::CCNode* node);
        virtual void updateNodeScale(cocos2d::CCNode* node);
    public:
        View(cocos2d::CCNode* node);
        View();
        ~View();

        void setFrame(const Rect& f);
        void setRotation(const Rotation& r);
        void setScale(const Scale& s);
        void setParentAnchor(const Anchor& a);
        void setAnchor(const Anchor& a);
        
        void addChild(IViewPtr child, unsigned layer=0);
        IViewPtr removeChild(const IView& child);
        void setParent(IView& parent);

        void setNode(cocos2d::CCNode* node);
        cocos2d::CCNode* getNode() const;

        void respondOnUpdate(UpdateEvent& event);
    };
    
}

#endif