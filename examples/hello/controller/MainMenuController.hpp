

#ifndef mvcgame_examples_hello_MainMenuController_hpp
#define mvcgame_examples_hello_MainMenuController_hpp

#include <mvcgame/controller/ViewController.hpp>
#include <mvcgame/Geometry.hpp>

class MainMenuController : public mvcgame::ViewController
{
private:
	static const mvcgame::gunit_t _titleSize;

	std::unique_ptr<mvcgame::View> createTitleView(const std::string& name, mvcgame::gunit_t y);
public:
	MainMenuController();
	void controllerAdded();
};

#endif