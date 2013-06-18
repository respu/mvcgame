#ifndef mvcgame_examples_hello_Application_hpp
#define mvcgame_examples_hello_Application_hpp

#include <mvcgame/base/Application.hpp>
#include "tiled/asset/AssetsManager.hpp"

class Application : public mvcgame::Application
{
private:
    AssetsManager _assets;
public:
    Application(std::unique_ptr<mvcgame::IApplicationBridge> bridge);

    const AssetsManager& getAssets() const;
    AssetsManager& getAssets();

    void run();
};

#endif