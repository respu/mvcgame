#ifndef mvcgame_examples_physics_Application_hpp
#define mvcgame_examples_physics_Application_hpp

#include <mvcgame/base/Application.hpp>

class Application : public mvcgame::Application
{

public:
    Application(std::unique_ptr<mvcgame::IApplicationBridge> bridge);

    void run();
};

#endif