//
//  View.cpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#include <mvcgame/View.hpp>
#include <assert.h>
#include <algorithm>

namespace mvcgame {

    View::View()
    {
    }

    View::View(const IView& v) :
    _frame(v.getFrame()), _scale(v.getScale()), _anchor(v.getAnchor()), _rotation(v.getRotation())
    {
    }

    View::View(const Rect& f, const Scale& s, const Anchor& a, const Rotation& r) :
    _frame(f), _scale(s), _anchor(a), _rotation(r)
    {
    }

    View::~View()
    {
    }

    void View::draw()
    {
    }

    const Rect& View::getFrame() const
    {
        return _frame;
    }

    void View::setFrame(const Rect& rect)
    {
        _frame = rect;
    }
    
    const Rotation& View::getRotation() const
    {
        return _rotation;
    }

    void View::setRotation(const Rotation& r)
    {
        _rotation = r;
    }
    
    const Scale& View::getScale() const
    {
        return _scale;
    }

    void View::setScale(const Scale& s)
    {
        _scale = s;
    }

    const Anchor& View::getAnchor() const
    {
        return _anchor;
    }

    void View::setAnchor(const Anchor& a)
    {
        _anchor = a;
    }

    void View::addChild(IView* child, unsigned layer)
    {
        // child should not exist
        assert(findChild(child) == _children.end());
        _children.push_back(IView::ChildWithLayer(child, layer));
    }

    void View::removeChild(IView* child)
    {
        _children.erase(findChild(child));
    }

    IView::Children::iterator View::findChild(IView* child)
    {
        return std::find_if(_children.begin(), _children.end(), [child](const IView::ChildWithLayer& elm){
            return elm.first == child;
        });
    }
}