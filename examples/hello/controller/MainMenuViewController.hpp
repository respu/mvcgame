

#ifndef mvcgame_examples_hello_MainMenuViewController_hpp
#define mvcgame_examples_hello_MainMenuViewController_hpp

#include <mvcgame/controller/ViewController.hpp>
#include <mvcgame/Pointers.hpp>
#include <mvcgame/Geometry.hpp>

class MainMenuViewController : public mvcgame::ViewController
{
private:
	static constexpr mvcgame::gunit_t _titleSize = 50;
	static constexpr mvcgame::gunit_t _optionSize = 40;

	mvcgame::IViewPtr createTitleView(const std::string& name, mvcgame::gunit_t y);
	mvcgame::IViewPtr createOptionView(const std::string& name, mvcgame::gunit_t y);
public:
	MainMenuViewController();
	void controllerAdded();
};

#endif