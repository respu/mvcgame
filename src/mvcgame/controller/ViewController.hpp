#ifndef mvcgame_ViewController_hpp
#define mvcgame_ViewController_hpp

#include <mvcgame/controller/BaseViewController.hpp>

namespace mvcgame {

    class ViewController : public BaseViewController
    {      
   	private:
   		IViewController* _parent;
   		IView* _view;
    protected:

        /**
         * called after the controller is added to a parent controller
         */
        virtual void controllerAdded();
    public:
    	ViewController();
    	virtual ~ViewController();

        const IView& getView() const;
        IView& getView();
        virtual void setView(IViewPtr view);

        const IViewController& getParent() const;
        IViewController& getParent();
        virtual void setParent(IViewController& parent);
        void removeFromParent();
    };

}

#endif