//
//  BaseView.cpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#include <mvcgame/view/BaseView.hpp>
#include <assert.h>
#include <algorithm>

namespace mvcgame {

    BaseView::BaseView() : _parent(nullptr)
    {
    }

    BaseView::BaseView(const IView& v) :
    BaseView(v.getFrame(), v.getScale(), v.getAnchor(), v.getRotation())
    {
    }

    BaseView::BaseView(const Rect& f, const Scale& s, const Anchor& a, const Rotation& r) :
    _parent(nullptr), _frame(f), _scale(s), _anchor(a), _rotation(r)
    {
    }

    BaseView::~BaseView()
    {
        for(ChildWithLayer& child : _children)
        {
            child.first->removeFromParent();
        }
        removeFromParent();
    }

    void BaseView::draw()
    {
    }

    Rect& BaseView::getFrame()
    {
        return _frame;
    }

    const Rect& BaseView::getFrame() const
    {
        return _frame;
    }

    void BaseView::setFrame(const Rect& rect)
    {
        _frame = rect;
    }
    
    Rotation& BaseView::getRotation()
    {
        return _rotation;
    }

    const Rotation& BaseView::getRotation() const
    {
        return _rotation;
    }

    void BaseView::setRotation(const Rotation& r)
    {
        _rotation = r;
    }
        
    Scale& BaseView::getScale()
    {
        return _scale;
    }

    const Scale& BaseView::getScale() const
    {
        return _scale;
    }

    void BaseView::setScale(const Scale& s)
    {
        _scale = s;
    }

    Anchor& BaseView::getAnchor()
    {
        return _anchor;
    }

    const Anchor& BaseView::getAnchor() const
    {
        return _anchor;
    }

    void BaseView::setAnchor(const Anchor& a)
    {
        _anchor = a;
    }

    Anchor& BaseView::getParentAnchor()
    {
        return _parentAnchor;
    }

    const Anchor& BaseView::getParentAnchor() const
    {
        return _parentAnchor;
    }

    void BaseView::setParentAnchor(const Anchor& a)
    {
        _parentAnchor = a;
    }    

    void BaseView::addChild(IViewPtr child, unsigned layer)
    {
        child->setParent(*this);
        _children.push_back(IView::ChildWithLayer(std::move(child), layer));
    }

    IViewPtr BaseView::removeChild(const IView& child)
    {
        IView::Children::iterator itr = findChild(child);
        if(itr == _children.end())
        {
            return IViewPtr();
        }
        IViewPtr childPtr = std::move(itr->first);
        _children.erase(itr);
        return childPtr;
    }

    IView::Children::iterator BaseView::findChild(const IView& child)
    {
        return std::find_if(_children.begin(), _children.end(), [&child](const IView::ChildWithLayer& elm){
            return elm.first.get() == &child;
        });
    }

    void BaseView::setParent(IView& parent)
    {
        _parent = &parent;
    }
    
    IView& BaseView::getParent()
    {
        return *_parent;
    }
    
    const IView& BaseView::getParent() const
    {
        return *_parent;
    }

    void BaseView::removeFromParent()
    {
        if(_parent != nullptr)
        {
            _parent->removeChild(*this);
            _parent = nullptr;
        }
    }

    bool BaseView::respondToTouchPoint(const Point& p, const TouchEvent& event)
    {
        return _frame.contains(p);
    }
}