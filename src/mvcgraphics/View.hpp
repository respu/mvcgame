//
//  View.hpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef hydra_View_hpp
#define hydra_View_hpp

#include <mvcgraphics/IView.hpp>
#include <mvcgraphics/Geometry.hpp>

namespace mvcgraphics {

    /**
     * This is a basic view class that doesn't draw anything
     * Can be used by the different platforms to inherit from.
     */
    class View : public IView
    {
    private:
        IView::Children _children;
        Rect _frame;
        Anchor _anchor;
        Scale _scale;
        Rotation _rotation;

    protected:
        IView::Children::iterator findChild(IView* child);
    public:
        View();
        View(const IView& view);
        View(const Rect& f, const Scale& s, const Anchor& a, const Rotation& r);
        virtual ~View();

        virtual void draw();

        virtual const Rect& getFrame() const;
        virtual void setFrame(const Rect& rect);
        
        virtual const Rotation& getRotation() const;
        virtual void setRotation(const Rotation& r);
        
        virtual const Scale& getScale() const;
        virtual void setScale(const Scale& s);

        virtual const Anchor& getAnchor() const;
        virtual void setAnchor(const Anchor& a);        
        
        virtual void addChild(IView* child, unsigned layer=0);
        virtual void removeChild(IView* child);
        
    };
}

#endif