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
        for(Child& child : _children)
        {
            child.first->removeFromParent();
        }
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
        _children.push_back(Child(std::move(child), layer));
    }

    std::unique_ptr<View> View::removeChild(const View& child)
    {
        Children::iterator itr = findChild(child);
        if(itr == _children.end())
        {
            return std::unique_ptr<View>();
        }
        std::unique_ptr<View> childPtr = std::move(itr->first);
        _children.erase(itr);
        return childPtr;
    }

    View::Children::iterator View::findChild(const View& child)
    {
        return std::find_if(_children.begin(), _children.end(), [&child](const View::Child& elm){
            return elm.first.get() == &child;
        });
    }

    void View::setParent(View& parent)
    {
        _parent = &parent;
    }
    
    View& View::getParent()
    {
        return *_parent;
    }
    
    const View& View::getParent() const
    {
        return *_parent;
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