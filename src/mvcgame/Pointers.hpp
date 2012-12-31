#ifndef mvcgame_Pointers_hpp
#define mvcgame_Pointers_hpp

#include <memory>

namespace mvcgame {
	class IView;
	class IViewController;

	typedef std::unique_ptr<IView> IViewPtr;
	typedef std::unique_ptr<IViewController> IViewControllerPtr;
}

#endif