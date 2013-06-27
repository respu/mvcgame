
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

        Point p(0, getFrame().size.height);

        for(unsigned ty=0; ty<layer.getHeight(); ty++)
        {   
            for(unsigned tx=0; tx<layer.getWidth(); tx++)
            {
                auto& tile = layer.getTile(tx, ty);
                auto sheet = _tileMap->getSheetForTypeId(tile.getTypeId());
                auto sprite = std::make_shared<Sprite>(sheet);
                sprite->getFrame().origin = p;
                addChild(sprite);
                
                if(tx < layer.getWidth()-1)
                {
                    p.x += sprite->getFrame().size.width;
                }
                else
                {
                    p.x = 0;
                    p.y -= sprite->getFrame().size.height;
                }
            }
        }
        _changed = false;
    }

    void TileMapView::draw()
    {
        View::draw();
    }
}