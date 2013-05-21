#ifndef mvcgame_BaseViewController_hpp
#define mvcgame_BaseViewController_hpp

#include <mvcgame/action/ActionRunner.hpp>
#include <mvcgame/event/IResponder.hpp>

namespace mvcgame {

    class ViewController;
    class RootViewController;

    class BaseViewController : public IResponder
    {
    public:
        typedef std::vector<std::unique_ptr<ViewController>> Children;
    private:
        Children _children;
    public:
        virtual ~BaseViewController();

        virtual void addChild(std::unique_ptr<ViewController> child);
        std::unique_ptr<ViewController> removeChild(const ViewController& child);
        Children::iterator findChild(const ViewController& child);
        const Children& getChildren() const;
        void clearChildren();
    };

}

#endif