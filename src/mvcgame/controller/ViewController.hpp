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
        ChildrenList _children;
        ActionRunner _actions;
        IView* _view;
    protected:
        void setView(IView* view);
        void clearChildren();
        void clearActions();
    public:
        ViewController();

        virtual ~ViewController();
        
        const IView& getView() const;
        IView& getView();
        
        void addChild(ViewController* child);

        const ChildrenList& getChildren() const;
        ChildrenList& getChildren();

        void runAction(IAction* action);
        void runAction(IAction* action, const Duration& duration);
        void updateActions(UpdateEvent& event);
    };
}

#endif
