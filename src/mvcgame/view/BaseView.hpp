
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
        typedef std::pair<std::unique_ptr<View>, unsigned> Child;
        typedef std::vector<Child> Children;
    protected:
        Children _children;
        Children::iterator findChild(const View& child);

    public:
        BaseView();
        virtual ~BaseView();

        virtual void addChild(std::unique_ptr<View> child, unsigned layer=0);
        std::unique_ptr<View> removeChild(const View& child);
        void removeChildren();

        virtual void update();
        virtual void draw();
    };
}

#endif