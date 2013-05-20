

#ifndef mvcgame_Application_hpp
#define mvcgame_Application_hpp

#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/platform/IApplicationBridge.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <memory>

namespace mvcgame {

	class ViewController;
    class IViewBridge;

	class Application
	{
    private:
        Size _size;
        std::unique_ptr<IApplicationBridge> _bridge;
        RootViewController _root;
	public:
        Application();
        const Size& getSize() const;
        RootViewController& getRoot();
        const RootViewController& getRoot() const;

        IViewBridge& getViewBridge();
        
		void run();
        void update();
	};
}

#endif