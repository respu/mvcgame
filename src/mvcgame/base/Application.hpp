

#ifndef mvcgame_Application_hpp
#define mvcgame_Application_hpp

#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/platform/IApplicationBridge.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/asset/AssetsManager.hpp>
#include <memory>

namespace mvcgame {

	class ViewController;

	class Application
	{
    private:
        Size _size;
        std::unique_ptr<IApplicationBridge> _bridge;
        RootViewController _root;
        AssetsManager _assets;
	public:
        Application(std::unique_ptr<IApplicationBridge> bridge);
        const Size& getSize() const;

		void run();
        void update();

        RootViewController& getRoot();
        const RootViewController& getRoot() const;

        IApplicationBridge& getBridge();
        const IApplicationBridge& getBridge() const;

        AssetsManager& getAssetsManager();
        const AssetsManager& getAssetsManager() const;
	};
}

#endif