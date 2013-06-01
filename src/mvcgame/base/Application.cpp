
#include <mvcgame/base/Application.hpp>
#include <mvcgame/view/RootView.hpp>

namespace mvcgame {

    Application::Application(std::unique_ptr<IApplicationBridge> bridge) :
    _bridge(std::move(bridge)),
    _root(*this)
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

    IApplicationBridge& Application::getBridge()
    {
        return *_bridge;
    }
    
    const IApplicationBridge& Application::getBridge() const
    {
        return *_bridge;
    }

    const Size& Application::getSize() const
    {
        return _root.getView().getSize();
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