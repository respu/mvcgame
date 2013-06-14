#ifndef mvcgame_ViewController_hpp
#define mvcgame_ViewController_hpp

#include <mvcgame/action/ActionRunner.hpp>
#include <mvcgame/controller/BaseViewController.hpp>

namespace mvcgame {

    class Application;
    class AssetsManager;
    class RootViewController;

    class ViewController : public BaseViewController
    {
	public:
		typedef std::vector<std::unique_ptr<ViewController>> Children;
   	private:
        Children _children;
        ActionRunner _actions;        
   		ViewController* _parent;
        RootViewController* _root;
   		std::shared_ptr<View> _view;
    protected:

        void moveChildren(View& view);
    public:
    	ViewController();
    	virtual ~ViewController();

        const View& getView() const;
        View& getView();
		virtual void setView(std::shared_ptr<View> view);

        void setRoot(RootViewController& root);
        const RootViewController& getRoot() const;
        RootViewController& getRoot();

        const Application& getApp() const;
        Application& getApp();

        const AssetsManager& getAssets() const;
        AssetsManager& getAssets();

        const ViewController& getParent() const;
        ViewController& getParent();
        virtual void setParent(ViewController& parent);
        void removeFromParent();
        
        void addChild(std::unique_ptr<ViewController> child);

        void runAction(std::unique_ptr<IAction> action, View& view);
        void runAction(std::unique_ptr<IAction> action, View& view, const Duration& duration);

        void updateActions(const UpdateEvent& event);

        void clearChildren();
        void clearActions();

        virtual bool respondToTouchPoint(const Point& p, const TouchEvent& event);
        virtual void respondOnUpdate(const UpdateEvent& event);        

        /**
         * called after the controller is added to a parent controller
         */
        virtual void controllerAdded();     
    };

}

#endif