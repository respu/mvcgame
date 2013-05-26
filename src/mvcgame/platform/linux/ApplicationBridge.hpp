#ifndef mvcgame_linux_ApplicationBridge_hpp
#define mvcgame_linux_ApplicationBridge_hpp

#include <mvcgame/platform/IApplicationBridge.hpp>
#include <mvcgame/platform/gl/ViewBridge.hpp>
#include <mvcgame/platform/linux/FilesystemBridge.hpp>

namespace mvcgame {

    class ApplicationBridge : public IApplicationBridge
    {
    private:
        Application* _app;
        bool _finished;
        ViewBridge _viewBridge;
        FilesystemBridge _fsBridge;
    public:
        ApplicationBridge();
        void run();
        void exit();
        void setApplication(Application& app);
        void showError(const std::string& error);
        IViewBridge& getViewBridge();
        IFilesystemBridge& getFilesystemBridge();
    };
}

#endif