
#include <mvcgame/base/Application.hpp>
#include <mvcgame/platform/ApplicationBridge.hpp>
#include <mvcgame/view/RootView.hpp>

namespace mvcgame {

    Application::Application() :
    _bridge(new ApplicationBridge()), _root(*this)
    {
        _bridge->setApplication(*this);
    }

    RootViewController& Application::getRoot()
    {
        return _root;
    }

    const RootViewController& Application::getRoot() const
    {
        return _root;
    }

    const Size& Application::getSize() const
    {
        return _root.getView().getSize();
    }

    IViewBridge& Application::getViewBridge()
    {
        return _bridge->getViewBridge();
    }

    void Application::run()
    {   
        _bridge->run();
    }

    void Application::update()
    {
        _root.emitUpdate();
    }
}