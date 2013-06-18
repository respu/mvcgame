

#ifndef mvcgame_examples_hello_MainController_hpp
#define mvcgame_examples_hello_MainController_hpp

#include <mvcgame/controller/ViewController.hpp>
#include <mvcgame/base/Geometry.hpp>

namespace mvcgame {
    class Sprite;
}

class MainController : public mvcgame::ViewController
{
private:
    std::shared_ptr<mvcgame::Sprite> _guybrush;
    mvcgame::Point _guybrushTouchPoint;
    bool _guybrushTouched;
public:
    MainController();
    void controllerAdded();
};

#endif