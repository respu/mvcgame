#include <mvcgame/platform/cocos2dx/Application.hpp>
#include <mvcgame/controller/ViewController.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/platform/cocos2dx/view/View.hpp>
#include <mvcgame/platform/cocos2dx/view/ColorView.hpp>

#include <unistd.h>
#include <string>

#include <cocos2dx/include/cocos2d.h>

#define MAXPATHLEN 1024

namespace mvcgame {

	class AppDelegate : public cocos2d::CCApplication
	{
	private:
		IViewControllerPtr _appCtrl;
		RootViewController _rootCtrl;

	public:
		
		AppDelegate(IViewControllerPtr appCtrl) : _appCtrl(std::move(appCtrl))
		{
		}

		bool applicationDidFinishLaunching()
		{
			// setup director
		    cocos2d::CCDirector* director = cocos2d::CCDirector::sharedDirector();
		    cocos2d::CCEGLView* glView = cocos2d::CCEGLView::sharedOpenGLView();
		    director->setOpenGLView(glView);
		    director->setDisplayStats(true);
		    director->setAnimationInterval(1.0 / 60);

		    // create root scene
		    cocos2d::CCScene* scene = new cocos2d::CCScene();
		    if(!scene->init())
		    {
		    	CC_SAFE_DELETE(scene);
		    	return false;
		    }
		    director->runWithScene(scene);

			// setup root controller
			cocos2d::CCSize size = glView->getFrameSize();
		    View* rootView = new View();
		    rootView->setFrame(Rect(Point(), Size(size.width, size.height)));
		    scene->addChild(rootView->getNode());
		    _rootCtrl.setView(IViewPtr(rootView));
		    _rootCtrl.addChild(std::move(_appCtrl));

		    return true;
		}

		void applicationDidEnterBackground()
		{
		    cocos2d::CCDirector::sharedDirector()->stopAnimation();
		}

		void applicationWillEnterForeground()
		{
		    cocos2d::CCDirector::sharedDirector()->startAnimation();
		}
	};

	Application::Application() : _ctrl(nullptr), _running(false)
	{
	}

	Application::~Application()
	{
	}

	void Application::setViewController(IViewControllerPtr ctrl)
	{
		assert(_running == false);
		_ctrl = std::move(ctrl);
	}

	void Application::setSize(const Size& size)
	{
		_size = size;
	}

	void Application::run()
	{
		assert(_running == false);
		assert(_ctrl != nullptr);

	    // create the application instance
		AppDelegate app(std::move(_ctrl));
		
	    // get resources path
	    int length;
	    char fullpath[MAXPATHLEN];
	    length = readlink("/proc/self/exe", fullpath, sizeof(fullpath));
	    fullpath[length] = '\0';
	    std::string resourcePath = fullpath;
	    resourcePath = resourcePath.substr(0, resourcePath.find_last_of("/"));
	    resourcePath += "/../../../Resources/";
	    app.setResourceRootPath(resourcePath.c_str());

	    // run the app
	    cocos2d::CCEGLView* glView = cocos2d::CCEGLView::sharedOpenGLView();
	    glView->setFrameSize(_size.width, _size.height);
	    _running = true;
	    app.run();
	    _running = false;
	}

}