#include "hello/controller/MainMenuController.hpp"

#include <mvcgame/platform/win/ApplicationBridge.hpp>
#include <mvcgame/base/Application.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/RootView.hpp>

#include <memory>
#include <windows.h>

using namespace mvcgame;

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	std::unique_ptr<ApplicationBridge> bridge(new ApplicationBridge());
	bridge->setInstance(hInstance);
	bridge->setCmdShow(nCmdShow);
	ApplicationBridge& bridgeRef = *bridge;

	mvcgame::Application app(std::move(bridge));
    app.getRoot().getView().setSize(Size(480, 320));
    app.getRoot().addChild(std::unique_ptr<MainMenuController>(new MainMenuController()));
    app.run();

	return bridgeRef.getCmdQuit();
}