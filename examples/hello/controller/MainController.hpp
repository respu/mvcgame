

#ifndef mvcgame_examples_hello_MainController_hpp
#define mvcgame_examples_hello_MainController_hpp

#include <mvcgame/controller/ViewController.hpp>
#include <mvcgame/base/Geometry.hpp>

class MainController : public mvcgame::ViewController
{
private:
	static const mvcgame::gunit_t _titleSize;

public:
	MainController();
	void controllerAdded();
};

#endif