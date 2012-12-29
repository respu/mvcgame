#ifndef mvcgame_BaseViewController_hpp
#define mvcgame_BaseViewController_hpp

#include <mvcgame/controller/IViewController.hpp>
#include <mvcgame/action/ActionRunner.hpp>

namespace mvcgame {

    class BaseViewController : public IViewController
    {
    private:
        IViewController::ChildrenList _children;
        ActionRunner _actions;
    protected:
        void moveChildren(IView& view);
    public:
        BaseViewController();
        virtual ~BaseViewController();
        
        void addChild(IViewControllerPtr child);
        void removeChild(const IViewController& child);

        const IViewController::ChildrenList& getChildren() const;
        IViewController::ChildrenList& getChildren();

        void runAction(IActionPtr action, const Duration& duration);
        void updateActions(UpdateEvent& event);

        void clearChildren();
        void clearActions();

    };
}

#endif
