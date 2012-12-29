//
//  ViewController.cpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#include <mvcgame/controller/ViewController.hpp>
#include <mvcgame/view/IView.hpp>

#include <algorithm>

namespace mvcgame {

    ViewController::ViewController() : _parent(nullptr), _view(nullptr)
    {

    }

    ViewController::~ViewController()
    {
        removeFromParent();
    	clearChildren();
        clearActions();
    }

    void ViewController::removeFromParent()
    {
        if(_parent != nullptr)
        {
            _parent->removeChild(*this);
            _parent = nullptr;
        }
    }

    void ViewController::setParent(IViewController& parent)
    {
        _parent = &parent;
    }

    IViewController& ViewController::getParent()
    {
        return *_parent;
    }

    const IViewController& ViewController::getParent() const
    {
        return *_parent;
    }

    void ViewController::clearChildren()
    {
        _children.clear();
    }

    void ViewController::clearActions()
    {
        _actions.clear();
    }

    void ViewController::setView(IViewPtr view)
    {
        _view = std::move(view);
    }
        
    const IView& ViewController::getView() const
    {
    	return *_view;
    }
    
    IView& ViewController::getView()
    {
    	return *_view;
    }
 
    void ViewController::addChild(IViewControllerPtr child)
    {
        child->setParent(*this);
    	_children.push_back(std::move(child));
        child->controllerAdded();
    }

    void ViewController::removeChild(const IViewController& child)
    {
        std::remove_if(_children.begin(), _children.end(), [&child](const std::unique_ptr<IViewController>& elm)
        {
            return elm.get() == &child;
        });
    }

    const IViewController::ChildrenList& ViewController::getChildren() const
    {
        return _children;
    }

    IViewController::ChildrenList& ViewController::getChildren()
    {
        return _children;
    }
    
    void ViewController::runAction(IActionPtr action, const Duration& duration)
    {
        _actions.add(std::move(action), duration);
    }

    void ViewController::updateActions(UpdateEvent& event)
    {
        _actions.update(getView(), event);
    }
}