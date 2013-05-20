
#ifndef mvcgame_View_hpp
#define mvcgame_View_hpp

#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/view/BaseView.hpp>

#include <vector>
#include <memory>

namespace mvcgame {

    class TouchEvent;
    class RootView;

    class View : public BaseView
    {
    protected:
        View* _parent;
        Rect _frame;
        Scale _scale;        
        Anchor _anchor;
        Anchor _parentAnchor;        
        Rotation _rotation;
        Transform _transform;

        void setParent(View& parent);
    public:
        View();
        View(const View& view);
        View(const Rect& f, const Scale& s, const Anchor& a, const Rotation& r);
        virtual ~View();

        virtual void draw();

        Rect& getFrame();
        const Rect& getFrame() const;
        void setFrame(const Rect& rect);

        Rotation& getRotation();
        const Rotation& getRotation() const;
        void setRotation(const Rotation& r);

        Scale& getScale();        
        const Scale& getScale() const;
        void setScale(const Scale& s);

        Anchor& getAnchor();
        const Anchor& getAnchor() const;
        void setAnchor(const Anchor& a);      
        
        Anchor& getParentAnchor();
        const Anchor& getParentAnchor() const;
        void setParentAnchor(const Anchor& a);

        View& getParent();
        const View& getParent() const;
        void removeFromParent();
        void addChild(std::unique_ptr<View> child, unsigned layer=0);

        RootView& getRoot();
        const RootView& getRoot() const;

        bool respondToTouchPoint(const Point& p, const TouchEvent& event);
    };
}

#endif