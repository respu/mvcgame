#include "tiled/base/Application.hpp"

#include <mvcgame/platform/win/ApplicationBridge.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/asset/FileStreamLoader.hpp>
#include <mvcgame/view/RootView.hpp>

#include <memory>
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	std::unique_ptr<mvcgame::ApplicationBridge> bridge(new mvcgame::ApplicationBridge());
	bridge->setInstance(hInstance);
	bridge->setCmdShow(nCmdShow);
	mvcgame::ApplicationBridge& bridgeRef = *bridge;

	Application app(std::move(bridge));

	std::unique_ptr<mvcgame::FileStreamLoader> fs(new mvcgame::FileStreamLoader(app.getBridge().getFilesystem()));
    fs->addPath("../../../tiled/hello/resources");
    app.getAssets().addStreamLoader(std::move(fs));

    app.run();

	return bridgeRef.getCmdQuit();
}