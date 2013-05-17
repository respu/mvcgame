

#ifndef mvcgame_examples_hello_MainMenuOptionController_hpp
#define mvcgame_examples_hello_MainMenuOptionController_hpp

#include <mvcgame/controller/ViewController.hpp>
#include <mvcgame/Geometry.hpp>

#include <string>

class MainMenuOptionController : public mvcgame::ViewController
{
private:
	static const mvcgame::gunit_t _textSize;
	std::string _text;
public:
	MainMenuOptionController(const std::string& text);
	void controllerAdded();
};

#endif