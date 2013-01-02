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

	class AppDelegate : public cocos2d::CCApplication, public cocos2d::CCObject, public cocos2d::CCTouchDelegate
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
			cocos2d::CCSize size = glView->getFrameSize();

		    // create root scene
		    cocos2d::CCScene* scene = new cocos2d::CCScene();
		    scene->setPosition(cocos2d::CCPointMake(size.width/2, size.height/2));
		    if(!scene->init())
		    {
		    	CC_SAFE_DELETE(scene);
		    	return false;
		    }
		    director->runWithScene(scene);

			// setup root controller
		    View* rootView = new View();
		    rootView->setFrame(Rect(Size(size.width, size.height)));
		    scene->addChild(rootView->getNode());
		    _rootCtrl.setView(IViewPtr(rootView));
		    _rootCtrl.addChild(std::move(_appCtrl));

		    director->getScheduler()->scheduleUpdateForTarget(this, 1, false);
		    director->getTouchDispatcher()->addStandardDelegate(this, 0);

		    return true;
		}

		void applicationDidEnterBackground()
		{
			cocos2d::CCDirector* director = cocos2d::CCDirector::sharedDirector();
		    director->stopAnimation();
		    director->getScheduler()->pauseTarget(this);
		}

		void applicationWillEnterForeground()
		{
			cocos2d::CCDirector* director = cocos2d::CCDirector::sharedDirector();
		    director->startAnimation();
		    director->getScheduler()->resumeTarget(this);
		}

		void update(float dt)
		{
			_rootCtrl.emitUpdate();
		}

		void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
		{

		}
   
     	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
     	{
     		
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