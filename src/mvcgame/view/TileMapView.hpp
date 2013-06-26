
#ifndef mvcgame_TileMapView_hpp
#define mvcgame_TileMapView_hpp

#include <mvcgame/view/View.hpp>
#include <mvcgame/tile/TileMap.hpp>
#include <memory>

namespace mvcgame {

    class TileMapView : public View
    {
    private:
        bool _changed;
        unsigned _layer;
        std::shared_ptr<TileMap> _tileMap;

    public:
        TileMapView();
        TileMapView(std::shared_ptr<TileMap> tileMap);

        void update();
        void draw();

        std::shared_ptr<TileMap> getTileMap();
        void setTileMap(std::shared_ptr<TileMap> tileMap);
    };
}

#endif