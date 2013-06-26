
#include <mvcgame/view/TileMapView.hpp>
#include <mvcgame/view/Sprite.hpp>

namespace mvcgame {

    TileMapView::TileMapView() :
    _changed(false),
    _layer(0)
    {
    }

    TileMapView::TileMapView(std::shared_ptr<TileMap> tileMap) :
    _changed(true),
    _layer(0),
    _tileMap(tileMap)
    {
    }

    std::shared_ptr<TileMap> TileMapView::getTileMap()
    {
        return _tileMap;
    }

    void TileMapView::setTileMap(std::shared_ptr<TileMap> tileMap)
    {
        if(_tileMap != tileMap)
        {
            _tileMap = tileMap;
            _changed = true;
        }
    }

    void TileMapView::update()
    {
        View::update();
        if(!_changed)
        {
            return;
        }
        removeChildren();
        TileLayer& layer = _tileMap->getLayers()[_layer];
    }

    void TileMapView::draw()
    {
        View::draw();
    }
}