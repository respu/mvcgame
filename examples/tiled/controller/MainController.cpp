
#include "tiled/controller/MainController.hpp"
#include "tiled/base/ServiceLocator.hpp"

#include <mvcgame/view/TileMapView.hpp>

using namespace mvcgame;

MainController::MainController()
{
}

void MainController::controllerAdded()
{
    auto tileMap = ServiceLocator::get().getTileMaps().load("desert");
    std::cout << *tileMap << std::endl;

    auto tileMapView = std::make_shared<TileMapView>(tileMap);
    setView(tileMapView);
}