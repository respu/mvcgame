
#include <mvcgame/view/BaseView.hpp>
#include <mvcgame/view/View.hpp>
#include <algorithm>

namespace mvcgame {

    BaseView::BaseView()
    {
    }

    BaseView::~BaseView()
    {
        removeChildren();
    }

    void BaseView::removeChildren()
    {
        for(Child& child : _children)
        {
            child.first->removeFromParent();
        }
        _children.clear();
    }

    void BaseView::addChild(std::unique_ptr<View> child, unsigned layer)
    {
        _children.push_back(Child(std::move(child), layer));
    }

    std::unique_ptr<View> BaseView::removeChild(const View& child)
    {
        Children::iterator itr = findChild(child);
        if(itr == _children.end())
        {
            return std::unique_ptr<View>();
        }
        std::unique_ptr<View> childPtr = std::move(itr->first);
        _children.erase(itr);
        return childPtr;
    }

    BaseView::Children::iterator BaseView::findChild(const View& child)
    {
        return std::find_if(_children.begin(), _children.end(), [&child](const View::Child& elm){
            return elm.first.get() == &child;
        });
    }

    void BaseView::update()
    {
        for(Child& child : _children)
        {
            child.first->update();
        }
    }

    void BaseView::draw()
    {
        for(Child& child : _children)
        {
            child.first->drawAsChild();
        }
    }

}