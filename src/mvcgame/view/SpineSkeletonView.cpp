

#include <mvcgame/view/SpineSkeletonView.hpp>
#include <mvcgame/event/Events.hpp>
#include <mvcgame/platform/IRenderBridge.hpp>
#include <mvcgame/texture/TextureAtlas.hpp>

namespace mvcgame {

    SpineSkeletonView::SpineSkeletonView() :
    _spineSkeleton(nullptr), _spineState(nullptr), _timeScale(1)
    {
    }

    SpineSkeletonView::SpineSkeletonView(std::shared_ptr<const SpineSkeleton> skeleton) :
    SpineSkeletonView()
    {
       setSkeleton(skeleton);
    }

    SpineSkeletonView::~SpineSkeletonView()
    {
        if(_spineState)
        {
            AnimationState_dispose(_spineState);
        }
        if(_spineSkeleton)
        {
            Skeleton_dispose(_spineSkeleton);
        }
    }

    std::shared_ptr<const SpineSkeleton> SpineSkeletonView::getSkeleton() const
    {
        return _skeleton;
    }

    void SpineSkeletonView::setSkeleton(std::shared_ptr<const SpineSkeleton> skeleton, bool changeSize)
    {
        if(_spineState)
        {
            AnimationState_dispose(_spineState);
        }
        if(_spineSkeleton)
        {
            Skeleton_dispose(_spineSkeleton);
        }      
        _skeleton = skeleton;
        _spineSkeleton = Skeleton_create(const_cast<SkeletonData*>(_skeleton->getSkeletonData()));
        _spineState = AnimationState_create(const_cast<AnimationStateData*>(_skeleton->getAnimationStateData()));

        AnimationState_setAnimationByName(_spineState, "walk", true);
        AnimationState_addAnimationByName(_spineState, "jump", false, 0);
        AnimationState_addAnimationByName(_spineState, "walk", true, 0);
        AnimationState_addAnimationByName(_spineState, "jump", false, 3);
        AnimationState_addAnimationByName(_spineState, "walk", true, 0);
        AnimationState_addAnimationByName(_spineState, 0, true, 0);
        AnimationState_addAnimationByName(_spineState, "walk", false, 1);         
    }

    void SpineSkeletonView::respondOnUpdate(const UpdateEvent& event)
    {
        float deltaTime = event.getInterval().fsecs();
        Skeleton_update(_spineSkeleton, deltaTime);
        AnimationState_update(_spineState, deltaTime * _timeScale);
        AnimationState_apply(_spineState, _spineSkeleton);
        Skeleton_updateWorldTransform(_spineSkeleton);        
    }

    void SpineSkeletonView::draw()
    {
        std::vector<Vertex> vertexArray;
        float vertexPositions[8];

        for (int i = 0; i < _spineSkeleton->slotCount; ++i)
        {
            Slot* slot = _spineSkeleton->slots[i];
            Attachment* attachment = slot->attachment;
            if (!attachment || attachment->type != ATTACHMENT_REGION)
            {
                continue;
            }
            RegionAttachment* regionAttachment = (RegionAttachment*)attachment;
            RegionAttachment_computeVertices(regionAttachment,
                slot->skeleton->x,
                slot->skeleton->y,
                slot->bone,
                vertexPositions);

            Vertex vertices[4];
            vertices[0].position.x = vertexPositions[VERTEX_X1];
            vertices[0].position.y = vertexPositions[VERTEX_Y1];
            vertices[1].position.x = vertexPositions[VERTEX_X2];
            vertices[1].position.y = vertexPositions[VERTEX_Y2];
            vertices[2].position.x = vertexPositions[VERTEX_X3];
            vertices[2].position.y = vertexPositions[VERTEX_Y3];
            vertices[3].position.x = vertexPositions[VERTEX_X4];
            vertices[3].position.y = vertexPositions[VERTEX_Y4];

            vertices[0].texture.x = regionAttachment->uvs[VERTEX_X1];
            vertices[0].texture.y = regionAttachment->uvs[VERTEX_Y1];
            vertices[1].texture.x = regionAttachment->uvs[VERTEX_X2];
            vertices[1].texture.y = regionAttachment->uvs[VERTEX_Y2];
            vertices[2].texture.x = regionAttachment->uvs[VERTEX_X3];
            vertices[2].texture.y = regionAttachment->uvs[VERTEX_Y3];
            vertices[3].texture.x = regionAttachment->uvs[VERTEX_X4];
            vertices[3].texture.y = regionAttachment->uvs[VERTEX_Y4];

            vertexArray.push_back(vertices[0]);
            vertexArray.push_back(vertices[1]);
            vertexArray.push_back(vertices[2]);
            vertexArray.push_back(vertices[3]);
        }
        getBridge().drawTexture(_skeleton->getTextureAtlas()->getTexture(), vertexArray);       
        View::draw();
    }

}