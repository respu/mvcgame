
#include <mvcgame/view/BaseView.hpp>
#include <mvcgame/view/View.hpp>
#include <algorithm>
#include <cassert>

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
        _children.clear();
    }

    void BaseView::addChild(std::shared_ptr<View> view, unsigned layer)
    {
        assert(view);
        _children.push_back(Child(view, layer));
    }

    std::shared_ptr<View> BaseView::removeChild(const View& view)
    {
        Children::iterator itr = findChild(view);
        if(itr == _children.end())
        {
            return std::shared_ptr<View>();
        }
        std::shared_ptr<View> childPtr = itr->first;
        _children.erase(itr);
        return childPtr;
    }

    BaseView::Children::iterator BaseView::findChild(const View& view)
    {
        return std::find_if(_children.begin(), _children.end(), [&view](const View::Child& elm){
            return elm.first.get() == &view;
        });
    }

    BaseView::Children& BaseView::getChildren()
    {
        return _children;
    }

    const BaseView::Children& BaseView::getChildren() const
    {
        return _children;
    }

    void BaseView::respondOnUpdate(const UpdateEvent& event)
    {
        update();
    }    

    void BaseView::update()
    {
    }

    void BaseView::draw()
    {
        for(Child& child : _children)
        {
            child.first->drawAsChild();
        }            
    }

}