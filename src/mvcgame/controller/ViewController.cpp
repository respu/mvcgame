
#include <mvcgame/controller/ViewController.hpp>
#include <mvcgame/view/IView.hpp>

#include <assert.h>
#include <algorithm>

namespace mvcgame {

    ViewController::ViewController() : _parent(nullptr), _view(nullptr)
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

    void ViewController::setParent(IViewController& parent)
    {
        if(_view != nullptr)
        {
            if(_parent != nullptr)
            {
                // remove view from old parent
                _parent->getView().removeChild(*_view).release();
            }
            parent.getView().addChild(IViewPtr(_view));
        }
        _parent = &parent;
        controllerAdded();
    }

    IViewController& ViewController::getParent()
    {
        assert(_parent != nullptr);
        return *_parent;
    }

    const IViewController& ViewController::getParent() const
    {
        assert(_parent != nullptr);
        return *_parent;
    }

    void ViewController::setView(IViewPtr view)
    {
        assert(_parent != nullptr);

        // set new view pointer
        IView* oldView = _view;
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
        
    const IView& ViewController::getView() const
    {
        assert(_view != nullptr);
        return *_view;
    }
    
    IView& ViewController::getView()
    {
        assert(_view != nullptr);
        return *_view;
    }

    void ViewController::controllerAdded()
    {
    }

}