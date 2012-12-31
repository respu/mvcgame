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
        updateNodeFrame(node);
        updateNodeRotation(node);
        updateNodeScale(node);
        updateNodeAnchor(node);
    }

    void View::updateNodeFrame(cocos2d::CCNode* node)
    {
        Rect f = _frame;

        /*
         in cocos2d, the child coordinates are from the child origin to the parent
         origin (0,0). In mvcgame the child coordinates are from the child anchor
         point to the parent anchor point.
        */
        if(_parent != nullptr)
        {
            // so if the view has a parent, we need to add the parent anchor
            f.origin += _parent->getAnchor()*_parent->getFrame().size;

        }

        // substract the anchor of the node
        f.origin -= _anchor*f.size;        
        
        _node->setPosition(cocos2d::CCPointMake(f.origin.x, f.origin.y));
        _node->setContentSize(cocos2d::CCSizeMake(f.size.width, f.size.height));        
    }

    void View::updateNodeRotation(cocos2d::CCNode* node)
    {
        const Rotation& r = _rotation;
        _node->setRotation(r.x);        
    }

    void View::updateNodeScale(cocos2d::CCNode* node)
    {
        const Scale& s = _scale;
        _node->setScaleX(s.x);
        _node->setScaleY(s.y);        
    }    

    void View::updateNodeAnchor(cocos2d::CCNode* node)
    {
        const Anchor& a = _anchor;
        _node->setAnchorPoint(cocos2d::CCPointMake(a.x, a.y));
        // update the frame since the cocos2d origin changes also
        updateNodeFrame(node);
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

    void View::setFrame(const Rect& f)
    {
    	BaseView::setFrame(f);
        updateNodeFrame(_node);
    }

    void View::setRotation(const Rotation& r)
    {
    	BaseView::setRotation(r);
    	updateNodeRotation(_node);
    }

    void View::setScale(const Scale& s)
    {
    	BaseView::setScale(s);
    	updateNodeScale(_node);
    }

    void View::setAnchor(const Anchor& a)
    {
        BaseView::setAnchor(a);
        updateNodeAnchor(_node);
    }

    void View::addChild(IViewPtr child, unsigned layer)
    {
        // expect the child to be a cocos view
        cocos2d::CCNode* childNode = static_cast<View*>(child.get())->getNode();
        assert(childNode != nullptr);
    	_node->addChild(childNode, layer);
        BaseView::addChild(IViewPtr(child.release()), layer);
    }

    IViewPtr View::removeChild(const IView& child)
    {
        // expect the child to be a cocos view
        cocos2d::CCNode* childNode = static_cast<const View&>(child).getNode();
        assert(childNode != nullptr);
        _node->removeChild(childNode, true);
    	return BaseView::removeChild(child);
    }

    void View::setParent(IView& parent)
    {
        // expect the parent to be a cocos view
        cocos2d::CCNode* parentNode = static_cast<View&>(parent).getNode();
        assert(parentNode != nullptr);
        _node->setParent(parentNode);
        BaseView::setParent(parent);
        // update the node position
        // since the coordinates in cocos are different than in mvcgame
        updateNodeFrame(_node);
    }

}