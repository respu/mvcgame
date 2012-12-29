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
        if(_view != nullptr)
        {
            delete _view;
        }
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
        _parent = &parent;
    }

    ViewController& ViewController::getParent()
    {
        return *_parent;
    }

    const ViewController& ViewController::getParent() const
    {
        return *_parent;
    }

    void ViewController::clearChildren()
    {
        for(const ViewController* child : _children)
        {
            delete child;
        }
        _children.clear();
    }

    void ViewController::clearActions()
    {
        _actions.clear();
    }

    void ViewController::setView(IView* view)
    {
        if(_view != nullptr)
        {
            delete _view;
        }
        _view = view;
    }
        
    const IView& ViewController::getView() const
    {
    	return *_view;
    }
    
    IView& ViewController::getView()
    {
    	return *_view;
    }
 
    void ViewController::addChild(ViewController* child)
    {
        child->setParent(*this);
    	_children.push_back(child);
        if(_view != nullptr)
        {
            _view->addChild(&child->getView());
        }
        child->controllerAdded();
    }

    void ViewController::removeChild(const ViewController& child)
    {
        std::remove_if(_children.begin(), _children.end(), [&child](const ViewController* elm){
            return elm == &child;
        });
    }

    const ViewController::ChildrenList& ViewController::getChildren() const
    {
        return _children;
    }

    ViewController::ChildrenList& ViewController::getChildren()
    {
        return _children;
    }
    
    void ViewController::runAction(IAction* action)
    {
        _actions.add(action);
    }
    
    void ViewController::runAction(IAction* action, const Duration& duration)
    {
        _actions.add(action, duration);
    }

    void ViewController::updateActions(UpdateEvent& event)
    {
        _actions.update(getView(), event);
    }

    void ViewController::controllerAdded()
    {

    }
}