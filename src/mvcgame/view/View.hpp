
#ifndef mvcgame_View_hpp
#define mvcgame_View_hpp

#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/view/BaseView.hpp>

#include <vector>
#include <memory>
#include <functional>

namespace mvcgame {

    class TouchEvent;
    class RootView;
    class IRenderBridge;

    class View : public BaseView, public std::enable_shared_from_this<View>
    {
    private:
        View* _parent;
        RootView* _root;
        Rect _frame;
        Scale _scale;
        Anchor _anchor;
        Rotation _rotation;
        Transform _transform;

        mutable bool _inverseDirty;
        mutable Transform _inverse;
        mutable bool _rootTransformDirty;
        mutable Transform _rootTransform;
        mutable bool _rootInverseDirty;        
        mutable Transform _rootInverse;
    protected:
        void setParent(View& parent);
        IRenderBridge& getBridge();
        void parentTransformChanged();
    public:
        View();
        View(const View& other);
        View(const Rect& f, const Scale& s, const Anchor& a, const Rotation& r);
        virtual ~View();

        virtual void update();
        void drawAsChild();

        Rect& getFrame();
        const Rect& getFrame() const;
        void setFrame(const Rect& rect);
        Rect getBoundingBox() const;

        Rotation& getRotation();
        const Rotation& getRotation() const;
        void setRotation(const Rotation& r);

        Scale& getScale();        
        const Scale& getScale() const;
        void setScale(const Scale& s);

        Anchor& getAnchor();
        const Anchor& getAnchor() const;
        void setAnchor(const Anchor& a);

        View& getParent();
        const View& getParent() const;
        void removeFromParent();
        void addChild(std::shared_ptr<View> view, unsigned layer=0);

        void setRoot(RootView& root);
        RootView& getRoot();
        const RootView& getRoot() const;

        const Transform& getTransform() const;
        const Transform& getRootTransform() const;
        const Transform& getInverse() const;
        const Transform& getRootInverse() const;

        bool respondToTouchPoint(const Point& p, const TouchEvent& event);
    };
}

#endif