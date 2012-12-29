

#ifndef mvcgame_IApplication_hpp
#define mvcgame_IApplication_hpp

namespace mvcgame {

	class ViewController;
	class Size;

	class IApplication
	{
	public:
		virtual ~IApplication(){}
		virtual void run() = 0;
		virtual void setSize(const Size& size) = 0;
		virtual void setRootViewController(ViewController* root) = 0;
	};
}

#endif