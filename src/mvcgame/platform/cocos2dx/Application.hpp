

#include <mvcgame/IApplication.hpp>

namespace mvcgame {
  
    class Application : public IApplication
    {
    private:
    	ViewController* _root;
    public:
		virtual ~Application();
		virtual void run();
		virtual void setRootViewController(ViewController* root);
    };
}