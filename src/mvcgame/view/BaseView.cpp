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

    BaseView::BaseView()
    {
    }

    BaseView::BaseView(const IView& v) :
    _frame(v.getFrame()), _scale(v.getScale()), _anchor(v.getAnchor()), _rotation(v.getRotation())
    {
    }

    BaseView::BaseView(const Rect& f, const Scale& s, const Anchor& a, const Rotation& r) :
    _frame(f), _scale(s), _anchor(a), _rotation(r)
    {
    }

    BaseView::~BaseView()
    {
        removeFromParent();
    }

    void BaseView::draw()
    {
    }

    const Rect& BaseView::getFrame() const
    {
        return _frame;
    }

    void BaseView::setFrame(const Rect& rect)
    {
        _frame = rect;
    }
    
    const Rotation& BaseView::getRotation() const
    {
        return _rotation;
    }

    void BaseView::setRotation(const Rotation& r)
    {
        _rotation = r;
    }
    
    const Scale& BaseView::getScale() const
    {
        return _scale;
    }

    void BaseView::setScale(const Scale& s)
    {
        _scale = s;
    }

    const Anchor& BaseView::getAnchor() const
    {
        return _anchor;
    }

    void BaseView::setAnchor(const Anchor& a)
    {
        _anchor = a;
    }

    void BaseView::addChild(IViewPtr child, unsigned layer)
    {
        child->setParent(*this);
        _children.push_back(IView::ChildWithLayer(std::move(child), layer));
    }

    void BaseView::removeChild(const IView& child)
    {
        _children.erase(findChild(child));
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
}