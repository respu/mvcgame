
#include <mvcgame/skeleton/SpineSkeleton.hpp>
#include <mvcgame/texture/TextureAtlas.hpp>

namespace mvcgame {

    SpineSkeleton::SpineSkeleton() :
    _skeletonData(nullptr), _animationStateData(nullptr)
    {
    }

    SpineSkeleton::SpineSkeleton(SkeletonData* data, std::shared_ptr<const TextureAtlas> atlas) :
    _skeletonData(nullptr), _animationStateData(nullptr), _atlas(atlas)
    {
        setSkeletonData(data);
    }

    SpineSkeleton::~SpineSkeleton()
    {
        if(_skeletonData)
        {
            SkeletonData_dispose(_skeletonData);
        }
        if(_animationStateData)
        {
            AnimationStateData_dispose(_animationStateData);
        }
    }

    void SpineSkeleton::setSkeletonData(SkeletonData* data)
    {
        if(_skeletonData)
        {
            SkeletonData_dispose(_skeletonData);
        }
        if(_animationStateData)
        {
            AnimationStateData_dispose(_animationStateData);
        }
        _skeletonData = data;
        _animationStateData = AnimationStateData_create(_skeletonData);     
    }

    void SpineSkeleton::setMix(const std::string& from, const std::string& to, float duration)
    {
        AnimationStateData_setMixByName(_animationStateData, from.c_str(), to.c_str(), duration);
    }

    const SkeletonData* SpineSkeleton::getSkeletonData() const
    {
        return _skeletonData;
    }

    SkeletonData* SpineSkeleton::getSkeletonData()
    {
        return _skeletonData;
    }

    const AnimationStateData* SpineSkeleton::getAnimationStateData() const
    {
        return _animationStateData;
    }

    AnimationStateData* SpineSkeleton::getAnimationStateData()
    {
        return _animationStateData;
    }

    void SpineSkeleton::setTextureAtlas(std::shared_ptr<const TextureAtlas> atlas)
    {
        _atlas = atlas;
    }

    std::shared_ptr<const TextureAtlas> SpineSkeleton::getTextureAtlas() const
    {
        return _atlas;
    }
    
    std::ostream& operator<<(std::ostream& os, const SpineSkeleton& s)
    {
        os << "SpineSkeleton(";
        os << *s.getTextureAtlas() << std::endl;
        os << ")";
        return os;
    }
}