
#ifndef mvcgame_cocos2dx_Application_hpp
#define mvcgame_cocos2dx_Application_hpp

#include <mvcgame/IApplication.hpp>
#include <mvcgame/Geometry.hpp>

namespace mvcgame {
  
    class Application : public IApplication
    {
    private:
        IViewControllerPtr _appController;
    	IViewControllerPtr _rootController;
        Size _size;
    public:
    	Application();
		~Application();
		void run();
        void setSize(const Size& size);
		void setRootViewController(IViewControllerPtr root);
    };
}

#endif