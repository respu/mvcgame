#include <mvcgame/view/View.hpp>
#include <assert.h>
#include <algorithm>

namespace mvcgame {

    View::View() : _parent(nullptr)
    {
    }

    View::View(const View& v) :
	_parent(nullptr), _frame(v.getFrame()), _scale(v.getScale()), _anchor(v.getAnchor()), _rotation(v.getRotation())
    {
    }

    View::View(const Rect& f, const Scale& s, const Anchor& a, const Rotation& r) :
    _parent(nullptr), _frame(f), _scale(s), _anchor(a), _rotation(r)
    {
    }

    View::~View()
    {
        removeFromParent();
    }

    void View::draw()
    {
    }

    Rect& View::getFrame()
    {
        return _frame;
    }

    const Rect& View::getFrame() const
    {
        return _frame;
    }

    void View::setFrame(const Rect& rect)
    {
        _frame = rect;
    }
    
    Rotation& View::getRotation()
    {
        return _rotation;
    }

    const Rotation& View::getRotation() const
    {
        return _rotation;
    }

    void View::setRotation(const Rotation& r)
    {
        _rotation = r;
    }
        
    Scale& View::getScale()
    {
        return _scale;
    }

    const Scale& View::getScale() const
    {
        return _scale;
    }

    void View::setScale(const Scale& s)
    {
        _scale = s;
    }

    Anchor& View::getAnchor()
    {
        return _anchor;
    }

    const Anchor& View::getAnchor() const
    {
        return _anchor;
    }

    void View::setAnchor(const Anchor& a)
    {
        _anchor = a;
    }

    Anchor& View::getParentAnchor()
    {
        return _parentAnchor;
    }

    const Anchor& View::getParentAnchor() const
    {
        return _parentAnchor;
    }

    void View::setParentAnchor(const Anchor& a)
    {
        _parentAnchor = a;
    }    

    void View::addChild(std::unique_ptr<View> child, unsigned layer)
    {
        child->setParent(*this);
        BaseView::addChild(std::move(child), layer);
    }

    void View::setParent(View& parent)
    {
        _parent = &parent;
    }
    
    View& View::getParent()
    {
        assert(_parent);
        return *_parent;
    }
    
    const View& View::getParent() const
    {
        assert(_parent);
        return *_parent;
    }

    RootView& View::getRoot()
    {
        return getParent().getRoot();
    }

    const RootView& View::getRoot() const
    {
        return getParent().getRoot();
    }

    void View::removeFromParent()
    {
        if(_parent != nullptr)
        {
            _parent->removeChild(*this);
            _parent = nullptr;
        }
    }

    bool View::respondToTouchPoint(const Point& p, const TouchEvent& event)
    {
        return _frame.contains(p);
    }
}