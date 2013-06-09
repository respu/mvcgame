#ifndef mvcgame_win_ApplicationBridge_hpp
#define mvcgame_win_ApplicationBridge_hpp

#include <mvcgame/platform/IApplicationBridge.hpp>
#include <mvcgame/platform/dx/RenderBridge.hpp>
#include <mvcgame/platform/win/FilesystemBridge.hpp>

#include <windows.h>

namespace mvcgame {

    class ApplicationBridge : public IApplicationBridge
    {
    private:
        Application* _app;
        RenderBridge _renderBridge;
        FilesystemBridge _fsBridge;

		HINSTANCE _instance;
		int _cmdShow;
		int _cmdQuit;
    public:
        ApplicationBridge();
        void run();
        void exit();
        void setApplication(Application& app);
        void showError(const std::string& error);

        IRenderBridge& getRender();
        IFilesystemBridge& getFilesystem();

		/**
		 windows specific stuff
		 */
		void setInstance(HINSTANCE instance);
		void setCmdShow(int cmdShow);
		int getCmdQuit() const;
    };
}

#endif