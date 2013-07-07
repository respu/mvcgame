#ifndef mvcgame_SpineSkeletonView_hpp
#define mvcgame_SpineSkeletonView_hpp

#include <mvcgame/view/View.hpp>
#include <mvcgame/skeleton/SpineSkeleton.hpp>

#include <spine/spine.h>
#include <spine/extension.h>

namespace mvcgame {

    class SpineSkeletonView : public View
    {
    private:
        std::shared_ptr<const SpineSkeleton> _skeleton;
        ::Skeleton* _spineSkeleton;
        ::AnimationState* _spineState;
        float _timeScale;
    public:
        SpineSkeletonView();
        SpineSkeletonView(std::shared_ptr<const SpineSkeleton> skeleton);
        ~SpineSkeletonView();

        std::shared_ptr<const SpineSkeleton> getSkeleton() const;
        void setSkeleton(std::shared_ptr<const SpineSkeleton> skeleton, bool changeSize=true);

        void respondOnUpdate(const UpdateEvent& event);
        void draw();
    };
}

#endif