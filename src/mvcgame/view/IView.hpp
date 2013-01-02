//
//  IView.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_IView_hpp
#define mvcgame_IView_hpp

#include <mvcgame/event/IResponder.hpp>
#include <memory>

namespace mvcgame {

    class IView;
    typedef std::unique_ptr<IView> IViewPtr;

    class IView : public IResponder
    {
    public:
        typedef std::pair<IViewPtr,unsigned> ChildWithLayer;
        typedef std::vector<ChildWithLayer> Children;

        virtual ~IView(){};
                
        /**
         * Draw should draw the view
         */
        virtual void draw() = 0;

        virtual const Rect& getFrame() const = 0;
        virtual Rect& getFrame() = 0;
        virtual void setFrame(const Rect& rect) = 0;
        
        virtual const Rotation& getRotation() const = 0;
        virtual Rotation& getRotation() = 0;
        virtual void setRotation(const Rotation& r) = 0;
        
        virtual const Scale& getScale() const = 0;
        virtual Scale& getScale() = 0;
        virtual void setScale(const Scale& s) = 0;

        /**
         * parent anchor represents the point that will connect
         * to the anchor of the parent view (getParent().getAnchor())
         */ 
        virtual const Anchor& getParentAnchor() const = 0;
        virtual Anchor& getParentAnchor() = 0;
        virtual void setParentAnchor(const Anchor& a) = 0;        

        virtual const Anchor& getAnchor() const = 0;
        virtual Anchor& getAnchor() = 0;
        virtual void setAnchor(const Anchor& a) = 0;

        virtual void addChild(IViewPtr child, unsigned layer=0) = 0;

        /**
         * should remove a child from the view
         * and return the unique_ptr to the removed child
         */
        virtual IViewPtr removeChild(const IView& child) = 0;

        virtual IView& getParent() = 0;
        virtual const IView& getParent() const = 0;
        virtual void removeFromParent() = 0;
        virtual void setParent(IView& parent) = 0;
        
    };
}

#endif