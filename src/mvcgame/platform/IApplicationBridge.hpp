

#ifndef mvcgame_IApplicationBridge_hpp
#define mvcgame_IApplicationBridge_hpp

#include <string>

namespace mvcgame {

    class Application;
    class IViewBridge;
    class IFilesystemBridge;

    class IApplicationBridge
    {
    public:
        virtual ~IApplicationBridge(){};

        virtual void run() = 0;
        virtual void exit() = 0;
        virtual void setApplication(Application& app) = 0;
        virtual void showError(const std::string& error) = 0;
        
        virtual IViewBridge& getViewBridge() = 0;
        virtual IFilesystemBridge& getFilesystemBridge() = 0;
    };

}

#endif