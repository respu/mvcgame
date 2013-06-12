

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
    static const mvcgame::gunit_t _titleSize;
    std::shared_ptr<mvcgame::Sprite> _guybrush;
public:
    MainController();
    void controllerAdded();
    void respondOnTouchStart(mvcgame::TouchEvent& event);
};

#endif