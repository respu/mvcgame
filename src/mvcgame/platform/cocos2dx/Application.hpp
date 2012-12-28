
#ifndef mvcgame_cocos2dx_Application_hpp
#define mvcgame_cocos2dx_Application_hpp

#include <mvcgame/IApplication.hpp>

namespace mvcgame {
  
    class Application : public IApplication
    {
    private:
    	ViewController* _root;
    public:
    	Application();
		~Application();
		void run();
		void setRootViewController(ViewController* root);
    };
}

#endif