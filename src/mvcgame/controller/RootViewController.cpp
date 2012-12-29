#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/IView.hpp>

#include <assert.h>

namespace mvcgame {

	RootViewController::RootViewController() : _view(nullptr)
	{
	}

	RootViewController::~RootViewController()
	{
        clearChildren();
	}

    const IView& RootViewController::getView() const
    {
    	assert(_view != nullptr);
		return *_view;
    }

    IView& RootViewController::getView()
    {
    	assert(_view != nullptr);
    	return *_view;
    }

    const IViewController& RootViewController::getParent() const
    {
		assert(false);
    }

    IViewController& RootViewController::getParent()
    {
    	assert(false);
    }

    void RootViewController::removeFromParent()
    {
    }

    void RootViewController::setParent(IViewController& parent)
    {
    	assert(false);
    }

    void RootViewController::setView(IViewPtr view)
    {
        // set new view pointer
        IViewPtr oldView = std::move(_view);
        _view = std::move(view);

        if(oldView != nullptr)
        {
            moveChildren(*oldView);
        }
    }
}