
#ifndef mvcgame_BaseView_hpp
#define mvcgame_BaseView_hpp

#include <mvcgame/event/IResponder.hpp>

#include <vector>
#include <memory>

namespace mvcgame {

    class View;

    class BaseView : public IResponder
    {
    public:       
        typedef std::pair<std::shared_ptr<View>, unsigned> Child;
        typedef std::vector<Child> Children;
    private:
        Children _children;
    protected:
        Children::iterator findChild(const View& view);
    public:
        BaseView();
        virtual ~BaseView();

        virtual void addChild(std::shared_ptr<View> view, unsigned layer=0);
        std::shared_ptr<View> removeChild(const View& view);
        void removeChildren();

        virtual void update();
        virtual void draw();
    };
}

#endif