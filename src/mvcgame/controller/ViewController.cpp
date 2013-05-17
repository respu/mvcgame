
#include <mvcgame/controller/ViewController.hpp>
#include <mvcgame/view/View.hpp>

#include <assert.h>
#include <algorithm>

namespace mvcgame {

    ViewController::ViewController() : _parent(nullptr), _view(nullptr)
    {
    }

    ViewController::~ViewController()
    {
        removeFromParent();
        clearChildren();
    }    

    void ViewController::removeFromParent()
    {
        if(_parent != nullptr)
        {
            _parent->removeChild(*this);
            _parent = nullptr;
        }
    }

    void ViewController::setParent(ViewController& parent)
    {
        if(_view != nullptr)
        {
            if(_parent != nullptr)
            {
                // remove view from old parent
                _parent->getView().removeChild(*_view).release();
            }
            parent.getView().addChild(std::unique_ptr<View>(_view));
        }
        _parent = &parent;
        controllerAdded();
    }

    ViewController& ViewController::getParent()
    {
        assert(_parent != nullptr);
        return *_parent;
    }

    const ViewController& ViewController::getParent() const
    {
        assert(_parent != nullptr);
        return *_parent;
    }

    void ViewController::setView(std::unique_ptr<View> view)
    {
        assert(_parent != nullptr);

        // set new view pointer
        View* oldView = _view;
        _view = view.get();

        if(oldView != nullptr)
        {
            // move all the child controller views to the new view
            moveChildren(*oldView);
            // remove the old view from the parent controller view
            _parent->getView().removeChild(*oldView);
        }

        // add the new view
        _parent->getView().addChild(std::move(view));
    }
        
    const View& ViewController::getView() const
    {
        assert(_view != nullptr);
        return *_view;
    }
    
    View& ViewController::getView()
    {
        assert(_view != nullptr);
        return *_view;
    }

    void ViewController::controllerAdded()
    {
    }

    void ViewController::clearChildren()
    {
        for(std::unique_ptr<ViewController>& child : _children)
        {
            child->getView().removeFromParent();
        }
        _children.clear();
    }

    void ViewController::clearActions()
    {
        _actions.clear();
    }
 
    void ViewController::addChild(std::unique_ptr<ViewController> child)
    {   
        ViewController& c = *child;
        _children.push_back(std::move(child));
        c.setParent(*this);
    }

    std::unique_ptr<ViewController> ViewController::removeChild(const ViewController& child)
    {
        Children::iterator itr = findChild(child);
        if(itr == _children.end())
        {
            return std::unique_ptr<ViewController>();
        }
        std::unique_ptr<ViewController> childPtr = std::move(*itr);
        _children.erase(itr);
        return childPtr;
    }

    ViewController::Children::iterator ViewController::findChild(const ViewController& child)
    {
		return std::find_if(_children.begin(), _children.end(), [&child](const std::unique_ptr<ViewController>& elm){
            return elm.get() == &child;
        });
    }

    const ViewController::Children& ViewController::getChildren() const
    {
        return _children;
    }

    void ViewController::runAction(std::unique_ptr<IAction> action, const Duration& duration)
    {
        _actions.add(std::move(action), duration);
    }

    void ViewController::updateActions(UpdateEvent& event)
    {
        _actions.update(getView(), event);
    }

    void ViewController::moveChildren(View& oldView)
    {
        View& view = getView();
		for(std::unique_ptr<ViewController>& child : _children)
        {
            std::unique_ptr<View> childView(oldView.removeChild(child->getView()));
            if(child != nullptr)
            {
                view.addChild(std::move(childView));
            }
        }
    }

    bool ViewController::respondToTouchPoint(const Point& p, const TouchEvent& event)
    {
        return getView().respondToTouchPoint(p, event);
    }

}