
#include <mvcgame/controller/BaseViewController.hpp>
#include <mvcgame/controller/ViewController.hpp>
#include <mvcgame/view/View.hpp>

#include <algorithm>

namespace mvcgame {

    BaseViewController::~BaseViewController()
    {
        clearChildren();
    }

    void BaseViewController::clearChildren()
    {
        for(std::unique_ptr<ViewController>& child : _children)
        {
            child->getView().removeFromParent();
        }
        _children.clear();
    }

    void BaseViewController::addChild(std::unique_ptr<ViewController> child)
    {   
        _children.push_back(std::move(child));
    }

    std::unique_ptr<ViewController> BaseViewController::removeChild(const ViewController& child)
    {
        Children::iterator itr = findChild(child);
        if(itr == _children.end())
        {
            return std::unique_ptr<ViewController>();
        }
        std::unique_ptr<ViewController> childPtr = std::move(*itr);
        _children.erase(itr);
        return childPtr;
    }

    ViewController::Children::iterator BaseViewController::findChild(const ViewController& child)
    {
        return std::find_if(_children.begin(), _children.end(), [&child](const std::unique_ptr<ViewController>& elm){
            return elm.get() == &child;
        });
    }

    const ViewController::Children& BaseViewController::getChildren() const
    {
        return _children;
    }

}