//
//  ViewController.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_IViewController_hpp
#define mvcgame_IViewController_hpp

#include <mvcgame/event/IResponder.hpp>
#include <mvcgame/action/IAction.hpp>
#include <memory>

namespace mvcgame {
    
    class IView;
    class IViewController;
    typedef std::unique_ptr<IView> IViewPtr;    
    typedef std::unique_ptr<IViewController> IViewControllerPtr;

    class IViewController : public IResponder
    {
    public:
        typedef std::vector<IViewControllerPtr> ChildrenList;

        virtual ~IViewController(){}        
        
        virtual const IView& getView() const = 0;
        virtual IView& getView() = 0;
        virtual void setView(std::unique_ptr<IView> view) = 0;

        virtual const IViewController& getParent() const = 0;
        virtual IViewController& getParent() = 0;
        virtual void setParent(IViewController& parent) = 0;
        
        virtual void addChild(IViewControllerPtr child) = 0;
        virtual void removeChild(const IViewController& child) = 0;

        virtual const ChildrenList& getChildren() const = 0;
        virtual ChildrenList& getChildren() = 0;

        void runAction(IActionPtr action)
        {
            runAction(std::move(action), Duration());
        }

        virtual void runAction(IActionPtr action, const Duration& duration) = 0;
        virtual void updateActions(UpdateEvent& event) = 0;

        virtual void clearChildren() = 0;
        virtual void clearActions() = 0;
        virtual void removeFromParent() = 0;

        /**
         * called after the controller is added to a parent controller
         */
        virtual void controllerAdded()
        {
        }
    };
}

#endif
