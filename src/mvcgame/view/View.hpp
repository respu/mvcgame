
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

    class View : public BaseView
    {
    public:
        typedef std::function<void(View& view)> ViewCallback;
    private:
        View* _parent;
        RootView* _root;
        Rect _frame;
        Scale _scale;
        Anchor _anchor;
        Rotation _rotation;
        Transform _transform;
        ViewCallback _removalCallback;
    protected:
        void setParent(View& parent);
        IRenderBridge& getBridge();
        void notifyRemoval(View& view);
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
        void addChild(std::unique_ptr<View> child, unsigned layer=0);

        void setRoot(RootView& root);
        RootView& getRoot();
        const RootView& getRoot() const;

        bool respondToTouchPoint(const Point& p, const TouchEvent& event);
        void setRemovalCallback(ViewCallback callback);
    };
}

#endif