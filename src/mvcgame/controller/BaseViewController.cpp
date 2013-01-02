//
//  ViewController.cpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#include <mvcgame/controller/BaseViewController.hpp>
#include <mvcgame/view/IView.hpp>

#include <assert.h>
#include <algorithm>

namespace mvcgame {

    BaseViewController::BaseViewController()
    {

    }

    BaseViewController::~BaseViewController()
    {
        clearChildren();
    }

    void BaseViewController::clearChildren()
    {
        for(IViewControllerPtr& child : _children)
        {
            child->getView().removeFromParent();
        }
        _children.clear();
    }

    void BaseViewController::clearActions()
    {
        _actions.clear();
    }
 
    void BaseViewController::addChild(IViewControllerPtr child)
    {   
        IViewController& c = *child;
    	_children.push_back(std::move(child));
        c.setParent(*this);
    }

    void BaseViewController::removeChild(const IViewController& child)
    {
        std::remove_if(_children.begin(), _children.end(), [&child](const std::unique_ptr<IViewController>& elm)
        {
            return elm.get() == &child;
        });
    }

    const IViewController::ChildrenList& BaseViewController::getChildren() const
    {
        return _children;
    }

    IViewController::ChildrenList& BaseViewController::getChildren()
    {
        return _children;
    }
    
    void BaseViewController::runAction(IActionPtr action, const Duration& duration)
    {
        _actions.add(std::move(action), duration);
    }

    void BaseViewController::updateActions(UpdateEvent& event)
    {
        _actions.update(getView(), event);
    }

    void BaseViewController::moveChildren(IView& oldView)
    {
        IView& view = getView();
        for(IViewControllerPtr& child : getChildren())
        {
            IViewPtr childView(oldView.removeChild(child->getView()));
            if(child != nullptr)
            {
                view.addChild(std::move(childView));
            }
        }
    }

    bool BaseViewController::respondToTouchPoint(const Point& p, const TouchEvent& event)
    {
        return getView().respondToTouchPoint(p, event);
    }
}