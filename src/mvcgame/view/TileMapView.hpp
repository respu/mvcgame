
#ifndef mvcgame_TileMapView_hpp
#define mvcgame_TileMapView_hpp

#include <mvcgame/view/View.hpp>
#include <mvcgame/tile/TileMap.hpp>
#include <memory>

namespace mvcgame {

    class TileLayer;

    class TileMapView : public View
    {
    private:
        bool _changed;
        TileLayer* _tileLayer;
        std::shared_ptr<TileMap> _tileMap;

    public:
        TileMapView();
        TileMapView(std::shared_ptr<TileMap> tileMap, bool changeSize=true);

        void update();
        void draw();

        void setTileLayer(unsigned int num, bool changeSize=true);
        void setTileLayer(const std::string& name, bool changeSize=true);

        std::shared_ptr<TileMap> getTileMap();
        void setTileMap(std::shared_ptr<TileMap> tileMap, bool changeSize=true);
    };
}

#endif