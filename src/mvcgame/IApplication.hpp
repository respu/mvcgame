

#ifndef mvcgame_IApplication_hpp
#define mvcgame_IApplication_hpp

#include <memory>

namespace mvcgame {

	class IViewController;
	class Size;
	typedef std::unique_ptr<IViewController> IViewControllerPtr;

	class IApplication
	{
	public:
		virtual ~IApplication(){}
		virtual void run() = 0;
		virtual void setSize(const Size& size) = 0;
		virtual void setRootViewController(IViewControllerPtr root) = 0;
	};
}

#endif