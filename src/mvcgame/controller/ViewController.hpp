//
//  ViewController.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_ViewController_hpp
#define mvcgame_ViewController_hpp

#include <mvcgame/controller/IViewController.hpp>
#include <mvcgame/action/ActionRunner.hpp>

namespace mvcgame {

    class ViewController : public IViewController
    {
    private:
        IViewController* _parent;
        IViewController::ChildrenList _children;
        ActionRunner _actions;
        IViewPtr _view;
    public:
        ViewController();
        virtual ~ViewController();
        
        const IView& getView() const;
        IView& getView();
        void setView(IViewPtr view);

        const IViewController& getParent() const;
        IViewController& getParent();
        void setParent(IViewController& parent);
        
        void addChild(IViewControllerPtr child);
        void removeChild(const IViewController& child);

        const IViewController::ChildrenList& getChildren() const;
        IViewController::ChildrenList& getChildren();

        void runAction(IActionPtr action, const Duration& duration);
        void updateActions(UpdateEvent& event);

        void clearChildren();
        void clearActions();
        void removeFromParent();
    };
}

#endif
