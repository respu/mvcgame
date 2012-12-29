

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
		virtual void setSize(const Size& size) = 0;
		virtual void setViewController(IViewControllerPtr ctrl) = 0;

		/**
		 * should be called after setting the root view controller
		 */
		virtual void run() = 0;
	};
}

#endif