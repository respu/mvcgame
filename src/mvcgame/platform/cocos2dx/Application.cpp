#include <mvcgame/platform/cocos2dx/Application.hpp>
#include <mvcgame/controller/ViewController.hpp>
#include <mvcgame/view/BaseView.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

#include <cocos2dx/include/cocos2d.h>

#define MAXPATHLEN 1024

namespace mvcgame {

	class AppDelegate : public cocos2d::CCApplication
	{
	public:
		
		AppDelegate()
		{
		}

		~AppDelegate() 
		{
		}

		bool applicationDidFinishLaunching()
		{
		    cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
		    cocos2d::CCEGLView* pEGLView = cocos2d::CCEGLView::sharedOpenGLView();
		    pDirector->setOpenGLView(pEGLView);
			
		    pDirector->setDisplayStats(true);
		    pDirector->setAnimationInterval(1.0 / 60);
		    cocos2d::CCScene *pScene = cocos2d::CCScene::create();
		    pDirector->runWithScene(pScene);

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

	Application::Application() : _appController(nullptr), _rootController(nullptr)
	{
	}

	Application::~Application()
	{
	}

	void Application::setRootViewController(IViewControllerPtr root)
	{
		if(_appController == nullptr)
		{
			_rootController = std::move(root);
		}
		else
		{
			_appController->clearChildren();
			_appController->addChild(std::move(root));
		}
	}

	void Application::setSize(const Size& size)
	{
		_size = size;
	}

	void Application::run()
	{
	    // get application path
	    int length;
	    char fullpath[MAXPATHLEN];
	    length = readlink("/proc/self/exe", fullpath, sizeof(fullpath));
	    fullpath[length] = '\0';

	    std::string resourcePath = fullpath;
	    resourcePath = resourcePath.substr(0, resourcePath.find_last_of("/"));
	    resourcePath += "/../../../Resources/";
	    
	    // create the application instance
	    AppDelegate app;
	    cocos2d::CCApplication::sharedApplication()->setResourceRootPath(resourcePath.c_str());
	    cocos2d::CCEGLView* eglView = cocos2d::CCEGLView::sharedOpenGLView();
	    eglView->setFrameSize(_size.width, _size.height);

	    cocos2d::CCApplication::sharedApplication()->run();

	    // setup fake app controller
	    _appController = IViewControllerPtr(new ViewController());
	    IViewPtr appView(new BaseView());
	    appView->setFrame(Rect(Point(), _size));
	    _appController->setView(std::move(appView));

	    if(_rootController != nullptr)
	    {
	    	_appController->addChild(std::move(_rootController));
	    }
	}

}