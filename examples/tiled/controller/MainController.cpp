
#include "tiled/controller/MainController.hpp"

#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/asset/AssetsManager.hpp>

using namespace mvcgame;

MainController::MainController()
{
}

void MainController::controllerAdded()
{
    auto desertMap = getAssets().load<TileMap>("desert");

    std::cout << *desertMap << std::endl;
}