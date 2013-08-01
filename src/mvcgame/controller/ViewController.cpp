
#include <mvcgame/controller/ViewController.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/View.hpp>
#include <mvcgame/view/RootView.hpp>
#include <mvcgame/base/Application.hpp>

#include <cassert>
#include <algorithm>

namespace mvcgame {

    ViewController::ViewController() :
    _parent(nullptr), _root(nullptr), _view(nullptr)
    {
    }

    ViewController::~ViewController()
    {
        removeFromParent();
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
        auto parentView = getParentView();
        if(parentView && _view)
        {
            // remove view from old parent
            parentView->removeChild(*_view);
        }
        _parent = &parent;
        parentView = getParentView();
        if(parentView && _view)
        {
            parentView->addChild(_view);
        }
        for(auto& child : getChildren())
        {
            child->setParent(*this);
        }
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

    bool ViewController::hasParent() const
    {
        return _parent != nullptr;
    }

    void ViewController::setRoot(RootViewController& root)
    {
        _root = &root;
    }

    bool ViewController::hasRoot() const
    {
        if(_root)
        {
            return true;
        }
        else if(_parent)
        {
            return _parent->hasRoot();
        }
        else
        {
            return false;
        }
    }

    RootViewController& ViewController::getRoot()
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

    const RootViewController& ViewController::getRoot() const
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

    const Application& ViewController::getApp() const
    {
        return getRoot().getApp();
    }

    Application& ViewController::getApp()
    {
        return getRoot().getApp();
    }

    BaseView* ViewController::getParentView()
    {
        BaseView* view = nullptr;
        if(!view && hasParent())
        {
            view = getParent().getView().get();
        }
        if(!view && hasParent())
        {
            view = getParent().getParentView();
        }        
        if(!view && hasRoot())
        {
            view = &getRoot().getView();
        }
        return view;
    }

    void ViewController::setView(std::shared_ptr<View> view)
    {
        // set new view pointer
        auto oldView = _view;
        _view = view;

        // move all the child controller views to the new view
        moveChildren(oldView.get());        

        auto parentView = getParentView();
        if(parentView)
        {
            if(oldView)
            {
                // remove the old view from the parent controller view
                parentView->removeChild(*oldView);
            }
            // add the new view
            parentView->addChild(view);
        }
    }
        
    std::shared_ptr<const View> ViewController::getView() const
    {
        return _view;
    }
    
    std::shared_ptr<View> ViewController::getView()
    {
        return _view;
    }

    void ViewController::controllerAdded()
    {
    }

    void ViewController::clearActions()
    {
        _actions.clear();
    }
 
    void ViewController::addChild(std::unique_ptr<ViewController> child)
    {   
        child->setParent(*this);      
        BaseViewController::addChild(std::move(child));
    }

    void ViewController::runAction(std::unique_ptr<IAction> action, View& view)
    {
        _actions.add(std::move(action), view);
    }

    void ViewController::runAction(std::unique_ptr<IAction> action, View& view, const Duration& duration)
    {
        _actions.add(std::move(action), view, duration);
    }

    void ViewController::updateActions(const UpdateEvent& event)
    {
        _actions.update(event);
    }

    void ViewController::moveChildren(View* oldView)
    {
        if(!_view)
        {
            return;
        }
    	for(auto& child : getChildren())
        {
            if(oldView)
            {
                oldView->removeChild(*child->getView());
            }
            auto childView = child->getView();
            if(childView)
            {
                _view->addChild(childView);
            }
        }
    }

    void ViewController::respondOnUpdate(const UpdateEvent& event)
    {
        updateActions(event);
    }

    bool ViewController::respondToTouchPoint(const Point& p, const TouchEvent& event)
    {
        if(!_view)
        {
            return false;
        }
        return _view->respondToTouchPoint(p, event);
    }

}