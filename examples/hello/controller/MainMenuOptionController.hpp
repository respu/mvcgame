

#ifndef mvcgame_examples_hello_MainMenuOptionController_hpp
#define mvcgame_examples_hello_MainMenuOptionController_hpp

#include <mvcgame/controller/ViewController.hpp>
#include <mvcgame/Geometry.hpp>

#include <string>

class MainMenuOptionController : public mvcgame::ViewController
{
private:
	static constexpr mvcgame::gunit_t _textSize = 40;
	std::string _text;
public:
	MainMenuOptionController(const std::string& text);
	void controllerAdded();
};

#endif