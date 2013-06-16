#include <mvcgame/view/View.hpp>
#include <mvcgame/view/RootView.hpp>
#include <mvcgame/platform/IRenderBridge.hpp>

#include <cassert>
#include <algorithm>

namespace mvcgame {

    View::View() : _parent(nullptr), _root(nullptr),
    _inverseDirty(false), _rootTransformDirty(false), _rootInverseDirty(false)
    {
    }

    View::View(const View& v) :
    _parent(v._parent), _root(v._root), _frame(v._frame), _scale(v._scale),
    _anchor(v._anchor), _rotation(v._rotation),
    _inverseDirty(false), _rootTransformDirty(false), _rootInverseDirty(false)
    {

    }

    View::View(const Rect& f, const Scale& s, const Anchor& a, const Rotation& r) :
    _parent(nullptr), _root(nullptr), _frame(f), _scale(s), _anchor(a), _rotation(r),
    _inverseDirty(false), _rootTransformDirty(false), _rootInverseDirty(false)    
    {
    }

    View::~View()
    {
    }

    void View::update()
    {
        if(_transform.update(_frame, _anchor, _rotation, _scale))
        {
            _inverseDirty = true;
            _rootTransformDirty = true;
            _rootInverseDirty = true;
        }
        BaseView::update();
    }

    void View::drawAsChild()
    {
        getBridge().pushTransform(_transform);
        draw();
        getBridge().popTransform(_transform);
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

    Rect View::getBoundingBox() const
    {
        Rect box = _frame;
        box.origin -= _anchor*box.size;
        return box;
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

    const Transform& View::getTransform() const
    {
        return _transform;
    }

    const Transform& View::getRootTransform() const
    {
        if(_rootTransformDirty)
        {
            _rootTransform = getParent().getTransform()*_transform;        
            _rootTransformDirty = false;
        }
        return _rootTransform;        
    }

    const Transform& View::getInverse() const
    {
        if(_inverseDirty)
        {
            _inverse = _transform.invert();        
            _inverseDirty = false;
        }
        return _inverse;        
    }

    const Transform& View::getRootInverse() const
    {
        if(_rootInverseDirty)
        {
            _rootInverse = getRootTransform().invert();
            _rootInverseDirty = false;
        }
        return _rootInverse;
    }

    void View::addChild(std::shared_ptr<View> child, unsigned layer)
    {
        child->setParent(*this);
        BaseView::addChild(child, layer);
    }

    void View::setParent(View& parent)
    {
        assert(!_parent);
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

    void View::setRoot(RootView& root)
    {
        _root = &root;
    }

    RootView& View::getRoot()
    {
        if(_root)
        {
            return *_root;
        }
        else
        {
            return getParent().getRoot();
        }
    }

    const RootView& View::getRoot() const
    {
        if(_root)
        {
            return *_root;
        }
        else
        {
            return getParent().getRoot();
        }
    }

    IRenderBridge& View::getBridge()
    {
        return getRoot().getBridge();
    }

    void View::removeFromParent()
    {
        if(_parent != nullptr)
        {
            View* p = _parent;
            _parent = nullptr;            
            p->removeChild(*this);
        }
    }

    bool View::respondToTouchPoint(const Point& p, const TouchEvent& event)
    {
        return _frame.size.contains(p);
    }  
}