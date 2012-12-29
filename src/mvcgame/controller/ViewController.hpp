//
//  ViewController.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_ViewController_hpp
#define mvcgame_ViewController_hpp

#include <mvcgame/event/IResponder.hpp>
#include <mvcgame/action/ActionRunner.hpp>

namespace mvcgame {
    
    class IView;

    class ViewController : public IResponder
    {
    public:
        typedef std::vector<ViewController*> ChildrenList;

    private:
        ViewController* _parent;
        ChildrenList _children;
        ActionRunner _actions;
        IView* _view;
    protected:
    public:
        ViewController();

        virtual ~ViewController();
        
        const IView& getView() const;
        IView& getView();
        void setView(IView* view);

        const ViewController& getParent() const;
        ViewController& getParent();
        void setParent(ViewController& parent);
        
        void addChild(ViewController* child);
        void removeChild(const ViewController& child);

        const ChildrenList& getChildren() const;
        ChildrenList& getChildren();

        void runAction(IAction* action);
        void runAction(IAction* action, const Duration& duration);
        void updateActions(UpdateEvent& event);

        void clearChildren();
        void clearActions();
        void removeFromParent();

        /**
         * called after the controller is added to a parent controller
         */
        virtual void controllerAdded();
    };
}

#endif
