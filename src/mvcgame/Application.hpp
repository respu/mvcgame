

#ifndef mvcgame_IApplication_hpp
#define mvcgame_IApplication_hpp

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