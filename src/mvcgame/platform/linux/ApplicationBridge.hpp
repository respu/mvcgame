#ifndef mvcgame_linux_ApplicationBridge_hpp
#define mvcgame_linux_ApplicationBridge_hpp

#include <mvcgame/platform/IApplicationBridge.hpp>
#include <mvcgame/platform/gl/RenderBridge.hpp>
#include <mvcgame/platform/linux/FilesystemBridge.hpp>

#include <X11/Xlib.h>

namespace mvcgame {

    class ApplicationBridge : public IApplicationBridge
    {
    private:
        Application* _app;
        bool _finished;
        RenderBridge _renderBridge;
        FilesystemBridge _fsBridge;

        void processEvent(XEvent& xev);
    public:
        ApplicationBridge();
        void run();
        void exit();
        void setApplication(Application& app);
        void showError(const std::string& error);
        IRenderBridge& getRender();
        IFilesystemBridge& getFilesystem();
    };
}

#endif