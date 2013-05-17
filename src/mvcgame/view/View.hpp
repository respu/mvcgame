//
//  View.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_View_hpp
#define mvcgame_View_hpp

#include <mvcgame/Geometry.hpp>
#include <mvcgame/event/IResponder.hpp>

#include <vector>
#include <memory>

namespace mvcgame {

    class TouchEvent;

    /**
     * This is a basic view class that doesn't draw anything
     * Can be used by the different platforms to inherit from.
     */
    class View : public IResponder
    {
    public:
        typedef std::pair<std::unique_ptr<View>, unsigned> Child;
        typedef std::vector<Child> Children;
    protected:
        View* _parent;
        View::Children _children;
        Rect _frame;
        Scale _scale;        
        Anchor _anchor;
        Anchor _parentAnchor;        
        Rotation _rotation;

        View::Children::iterator findChild(const View& child);

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

        void addChild(std::unique_ptr<View> child, unsigned layer=0);
        std::unique_ptr<View> removeChild(const View& child);

        View& getParent();
        const View& getParent() const;
        void removeFromParent();

        bool respondToTouchPoint(const Point& p, const TouchEvent& event);
    };
}

#endif