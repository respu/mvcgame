

#ifndef mvcgame_Application_hpp
#define mvcgame_Application_hpp

#include <memory>

namespace mvcgame {

	class ViewController;
	class Size;

	class Application
	{
	public:
		void setSize(const Size& size);
		void setViewController(std::unique_ptr<ViewController> ctrl);
		void run();
	};
}

#endif