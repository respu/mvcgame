
#include "tiled/controller/MainController.hpp"
#include "tiled/base/ServiceLocator.hpp"

#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/TileMapView.hpp>
#include <mvcgame/view/PanZoomView.hpp>

using namespace mvcgame;

MainController::MainController()
{
}

void MainController::controllerAdded()
{
    auto tileMap = ServiceLocator::get().getTileMaps().load("desert");
    std::cout << *tileMap << std::endl;

    auto tileMapView = std::make_shared<TileMapView>(tileMap);
    tileMapView->getFrame().size = getRoot().getView().getSize();
    tileMapView->getFrame().origin = tileMapView->getFrame().size/2;

    auto panZoom = std::make_shared<PanZoomView>();
    panZoom->setFrame(tileMapView->getFrame());
    panZoom->setContentView(tileMapView);

    setView(panZoom);
}