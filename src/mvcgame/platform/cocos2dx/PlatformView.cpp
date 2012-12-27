//
//  PlatformView.cpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#include <mvcgame/platform/cocos2dx/PlatformView.hpp>
#include <mvcgame/Geometry.hpp>

namespace mvcgame {

	PlatformView::PlatformView(cocos2d::CCNode* node) : _node(node)
	{
		setNode(node);
	}

    PlatformView::PlatformView()
    {
    	_node = new cocos2d::CCNode();
    	setNode(_node);
    }

    PlatformView::~PlatformView()
    {
    	CC_SAFE_RELEASE(_node);
    	Children::const_iterator itr;
    	for(itr=_children.begin(); itr!=_children.end(); ++itr)
    	{
    		delete itr->first;
    	}
    }

    void  PlatformView::setNode(cocos2d::CCNode* node)
    {
    	_node = node;
    	const cocos2d::CCSize& size = node->getContentSize();
        View::setFrame(Rect(node->getPositionX(), node->getPositionY(), size.width, size.height));
        View::setScale(Scale(node->getScaleX(), node->getScaleY()));
        View::setRotation(Rotation(node->getRotation(), 0));
        const cocos2d::CCPoint& a = node->getAnchorPoint();
        View::setAnchor(Anchor(a.x, a.y));
    }

    void PlatformView::setFrame(const Rect& rect)
    {
    	View::setFrame(rect);
    	_node->setPosition(cocos2d::CCPointMake(rect.origin.x, rect.origin.y));
    	_node->setContentSize(cocos2d::CCSizeMake(rect.size.width, rect.size.height));
    }

    void PlatformView::setRotation(const Rotation& r)
    {
    	View::setRotation(r);
    	_node->setRotation(r.x);    	
    }

    void PlatformView::setScale(const Scale& s)
    {
    	setScale(s);
    	_node->setScaleX(s.x);
    	_node->setScaleY(s.y);
    }

    void PlatformView::setAnchor(const Anchor& a)
    {
        setAnchor(a);
        _node->setAnchorPoint(cocos2d::CCPointMake(a.x, a.y));
    }
    
    void PlatformView::addChild(IView* child, unsigned layer)
    {
        View::addChild(child);
        PlatformView* pchild = static_cast<PlatformView*>(child);
    	_node->addChild(pchild->_node, layer);
    }

    void PlatformView::removeChild(IView* child)
    {
    	View::removeChild(child);
        PlatformView* pchild = static_cast<PlatformView*>(child);
        _node->removeChild(pchild->_node, true);
    }

}