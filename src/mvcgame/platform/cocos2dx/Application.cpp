

#include <mvcgame/platform/cocos2dx/Application.hpp>
#include <mvcgame/ViewController.hpp>

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

		void applicationDidEnterBackground() {
		    cocos2d::CCDirector::sharedDirector()->stopAnimation();
		}

		void applicationWillEnterForeground() {
		    cocos2d::CCDirector::sharedDirector()->startAnimation();
		}
	};

	Application::~Application()
	{
		delete _root;
	}

	void Application::setRootViewController(ViewController* root)
	{
		_root = root;
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
	    eglView->setFrameSize(480, 320);

	    cocos2d::CCApplication::sharedApplication()->run();
	}

}