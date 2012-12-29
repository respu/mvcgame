//
//  View.cpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#include <mvcgame/platform/cocos2dx/view/View.hpp>
#include <mvcgame/Geometry.hpp>
#include <cocos2dx/base_nodes/CCNode.h>

namespace mvcgame {

	View::View(cocos2d::CCNode* node) : _node(node)
	{
		updateNode(_node);
	}

    View::View() : View(new cocos2d::CCNode())
    {
    }

    View::~View()
    {
    	CC_SAFE_RELEASE(_node);
    }

    void View::updateNode(cocos2d::CCNode* node)
    {
        const Rect& rect = getFrame();
        _node->setPosition(cocos2d::CCPointMake(rect.origin.x, rect.origin.y));
        _node->setContentSize(cocos2d::CCSizeMake(rect.size.width, rect.size.height));
        const Rotation& rot = getRotation();
        _node->setRotation(rot.x);
        const Scale& s = getScale();
        _node->setScaleX(s.x);
        _node->setScaleY(s.y);
        const Anchor& a = getAnchor();
        _node->setAnchorPoint(cocos2d::CCPointMake(a.x, a.y));
    }

    void View::setNode(cocos2d::CCNode* node)
    {
        if(_node != node)
        {
            if(_node != nullptr)
            {
                CC_SAFE_RELEASE(_node);
            }
        	_node = node;
            CC_SAFE_RETAIN(_node);
        }
    	const cocos2d::CCSize& size = node->getContentSize();
        BaseView::setFrame(Rect(node->getPositionX(), node->getPositionY(), size.width, size.height));
        BaseView::setScale(Scale(node->getScaleX(), node->getScaleY()));
        BaseView::setRotation(Rotation(node->getRotation(), 0));
        const cocos2d::CCPoint& a = node->getAnchorPoint();
        BaseView::setAnchor(Anchor(a.x, a.y));
    }

    cocos2d::CCNode* View::getNode() const
    {
        return _node;
    }

    void View::setFrame(const Rect& rect)
    {
    	BaseView::setFrame(rect);
    	_node->setPosition(cocos2d::CCPointMake(rect.origin.x, rect.origin.y));
    	_node->setContentSize(cocos2d::CCSizeMake(rect.size.width, rect.size.height));
    }

    void View::setRotation(const Rotation& r)
    {
    	BaseView::setRotation(r);
    	_node->setRotation(r.x);	
    }

    void View::setScale(const Scale& s)
    {
    	BaseView::setScale(s);
    	_node->setScaleX(s.x);
    	_node->setScaleY(s.y);
    }

    void View::setAnchor(const Anchor& a)
    {
        BaseView::setAnchor(a);
        _node->setAnchorPoint(cocos2d::CCPointMake(a.x, a.y));
    }

    void View::addChild(IViewPtr child, unsigned layer)
    {
        cocos2d::CCNode* childNode = static_cast<View*>(child.get())->getNode();
        assert(childNode);
    	_node->addChild(childNode, layer);
        BaseView::addChild(IViewPtr(child.release()), layer);
    }

    IViewPtr View::removeChild(const IView& child)
    {
        cocos2d::CCNode* childNode = static_cast<const View&>(child).getNode();
        assert(childNode);
        _node->removeChild(childNode, true);
    	return BaseView::removeChild(child);
    }

    void View::setParent(IView& parent)
    {
        cocos2d::CCNode* parentNode = static_cast<View&>(parent).getNode();
        assert(parentNode);
        _node->setParent(parentNode);
        BaseView::setParent(parent);
    }

}