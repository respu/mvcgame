
#include "tiled/controller/MainController.hpp"
#include "tiled/base/ServiceLocator.hpp"

using namespace mvcgame;

MainController::MainController()
{
}

void MainController::controllerAdded()
{
    auto desertMap = ServiceLocator::get().getTileMaps().load("desert");
    std::cout << *desertMap << std::endl;
}