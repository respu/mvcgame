
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

        Point p(0, 0);
        unsigned th = layer.getHeight();
        unsigned tw = layer.getWidth();
        std::vector<std::shared_ptr<Sprite>> tiles;
        Rect tr;
        for(unsigned ty=0; ty<th; ty++)
        {   
            for(unsigned tx=0; tx<tw; tx++)
            {
                auto& tile = layer.getTile(tx, ty);
                auto sheet = _tileMap->getSheetForTypeId(tile.getTypeId());
                auto sprite = std::make_shared<Sprite>(sheet);
                tiles.push_back(sprite);
                sprite->getFrame().origin = p;
                if(tx < tw-1)
                {
                    p.x += sprite->getFrame().size.width;
                }
                else
                {
                    p.x = 0;
                    p.y -= sprite->getFrame().size.height;
                }
                tr += sprite->getFrame();
            }
        }
        std::cout << tr << std::endl;
        Scale sc = getFrame().size / tr.size;
        for(std::shared_ptr<Sprite>& tile : tiles)
        {
            tile->setScale(sc);
            tile->setAnchor(Anchor(0,1));            
            tile->getFrame().origin *= sc;
            tile->getFrame().origin.y += getFrame().size.height;
            addChild(tile);
        }
        _changed = false;
    }

    void TileMapView::draw()
    {
        View::draw();
    }
}