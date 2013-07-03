
#include "tiled/controller/MainController.hpp"
#include "tiled/base/ServiceLocator.hpp"

#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/TileMapView.hpp>
#include <mvcgame/view/PanZoomView.hpp>
#include <mvcgame/view/ColorView.hpp>

using namespace mvcgame;

MainController::MainController()
{
}

void MainController::controllerAdded()
{
    auto bg = std::make_shared<ColorView>();
    bg->setBackgroundColor(Color(100, 100, 100));
    bg->getFrame().size = getRoot().getView().getSize();
    bg->getFrame().origin = bg->getFrame().size/2;

    auto tileMap = ServiceLocator::get().getTileMaps().load("desert");
    std::cout << *tileMap << std::endl;

    auto tileMapView = std::make_shared<TileMapView>(tileMap);
    tileMapView->getFrame().origin = tileMapView->getFrame().size/2;

    auto panZoom = std::make_shared<PanZoomView>();
    panZoom->setFrame(tileMapView->getFrame());
    panZoom->setContentView(tileMapView);

    bg->addChild(panZoom);
    setView(bg);
}