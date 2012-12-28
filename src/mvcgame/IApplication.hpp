

#ifndef mvcgame_IApplication_hpp
#define mvcgame_IApplication_hpp

namespace mvcgame {

	class ViewController;

	class IApplication
	{
	public:
		virtual ~IApplication(){}
		virtual void run() = 0;
		virtual void setRootViewController(ViewController* root) = 0;
	};
}

#endif