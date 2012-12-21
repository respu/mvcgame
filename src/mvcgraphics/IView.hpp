//
//  IView.hpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef hydra_IView_hpp
#define hydra_IView_hpp

#include <mvcgraphics/IResponder.hpp>

namespace mvcgraphics {
    class IView : public IResponder
    {
    public:
        typedef std::pair<IView*,unsigned> ChildWithLayer;
        typedef std::vector<ChildWithLayer> Children;

        virtual ~IView(){};
                
        /**
         * Draw should draw the view
         */
        virtual void draw() = 0;

        virtual const Rect& getFrame() const = 0;
        virtual void setFrame(const Rect& rect) = 0;
        
        virtual const Rotation& getRotation() const = 0;
        virtual void setRotation(const Rotation& r) = 0;
        
        virtual const Scale& getScale() const = 0;
        virtual void setScale(const Scale& s) = 0;
        
        virtual const Anchor& getAnchor() const = 0;
        virtual void setAnchor(const Anchor& a) = 0;

        /**
         * The added children should be deleted when the parent is.
         */
        virtual void addChild(IView* child, unsigned layer=0) = 0;
        
        virtual void removeChild(IView* child) = 0;        
        
    };
}

#endif