

#ifndef mvcgame_Application_hpp
#define mvcgame_Application_hpp

#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/platform/IApplicationBridge.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <memory>

namespace mvcgame {

	class ViewController;
    class AssetsManager;

	class Application
	{
    private:
        Size _size;
        std::unique_ptr<IApplicationBridge> _bridge;
        RootViewController _root;
	public:
        Application(std::unique_ptr<IApplicationBridge> bridge);
        const Size& getSize() const;

		virtual void run();
        void update();

        RootViewController& getRoot();
        const RootViewController& getRoot() const;

        IApplicationBridge& getBridge();
        const IApplicationBridge& getBridge() const;

        virtual AssetsManager& getAssets() = 0;
        virtual const AssetsManager& getAssets() const = 0;
	};
}

#endif