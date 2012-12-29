#ifndef mvcgame_RootViewController_hpp
#define mvcgame_RootViewController_hpp

#include <mvcgame/controller/BaseViewController.hpp>

namespace mvcgame {

    class RootViewController : public BaseViewController
    {
    private:
    	IViewPtr _view;
    public:
    	RootViewController();
    	~RootViewController();

        const IView& getView() const;
        IView& getView();
        void setView(IViewPtr view);

        const IViewController& getParent() const;
        IViewController& getParent();
        void setParent(IViewController& parent);
        void removeFromParent();
    };
}

#endif