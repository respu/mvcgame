
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

    void ViewController::setRoot(RootViewController& root)
    {
        _root = &root;
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

    const AssetsManager& ViewController::getAssetsManager() const
    {
        return getApp().getAssetsManager();
    }

    AssetsManager& ViewController::getAssetsManager()
    {
        return getApp().getAssetsManager();
    }

    void ViewController::setView(std::unique_ptr<View> view)
    {
        BaseView* parentView = nullptr;
        if(_parent)
        {
            parentView = &_parent->getView();
        }
        else
        {
            parentView = &_root->getView();
        }
        assert(parentView);

        // set new view pointer
        View* oldView = _view;
        _view = view.get();

        if(oldView != nullptr)
        {
            // move all the child controller views to the new view
            moveChildren(*oldView);
            // remove the old view from the parent controller view
            parentView->removeChild(*oldView);
        }

        // get notifications when a view is removed so that
        // the controller can stop actions and clear its view ref
        view->setRemovalCallback(std::bind(&ViewController::onViewRemoved, this, std::placeholders::_1));

        // add the new view
        parentView->addChild(std::move(view));
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

    void ViewController::updateActions(UpdateEvent& event)
    {
        _actions.update(event);
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

    void ViewController::respondOnUpdate(UpdateEvent& event)
    {
        updateActions(event);
    }

    bool ViewController::respondToTouchPoint(const Point& p, const TouchEvent& event)
    {
        return getView().respondToTouchPoint(p, event);
    }

    void ViewController::onViewRemoved(View& view)
    {
        if(_view == &view)
        {
            _view = nullptr;
        }
        _actions.remove(view);
    }

}