#ifndef mvcgame_SpineSkeleton_hpp
#define mvcgame_SpineSkeleton_hpp

#include <memory>
#include <iostream>

#include <spine/spine.h>

namespace mvcgame {

    class TextureAtlas;

    class SpineSkeleton
    {
    private:
        SkeletonData* _skeletonData;
        AnimationStateData* _animationStateData;
        std::shared_ptr<const TextureAtlas> _atlas;
    public:
        SpineSkeleton();
        SpineSkeleton(SkeletonData* data, std::shared_ptr<const TextureAtlas> atlas);

        ~SpineSkeleton();

        void setSkeletonData(SkeletonData* data);
        const SkeletonData* getSkeletonData() const;
        SkeletonData* getSkeletonData();

        const AnimationStateData* getAnimationStateData() const;
        AnimationStateData* getAnimationStateData();        

        void setTextureAtlas(std::shared_ptr<const TextureAtlas> atlas);
        std::shared_ptr<const TextureAtlas> getTextureAtlas() const;
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const SpineSkeleton& s);    

}

#endif