
#include <mvcgame/skeleton/SpineSkeletonLoader.hpp>
#include <mvcgame/asset/AssetManager.hpp>
#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/texture/TextureAtlas.hpp>
#include <mvcgame/texture/TextureRegion.hpp>
#include <mvcgame/skeleton/Skeleton.hpp>

#include <spine/spine.h>
#include <spine/extension.h>

#include <cassert>

#pragma mark - spine functions

void _AtlasPage_createTexture (AtlasPage* self, const char* path)
{
    assert(false);
}

void _AtlasPage_disposeTexture (AtlasPage* self)
{
    assert(false);
}

char* _Util_readFile (const char* path, int* length)
{
    assert(false);
    return _readFile(path, length);
}


namespace mvcgame {

#pragma mark - spine attachment loader

    typedef struct
    {
        AttachmentLoader super;
        TextureAtlas* atlas;
    } AtlasAttachmentLoader;

    Attachment* _AtlasAttachmentLoaderr_newAttachment(AttachmentLoader* loader, Skin* skin, AttachmentType type, const char* name)
    {
        AtlasAttachmentLoader* self = SUB_CAST(AtlasAttachmentLoader, loader);
        switch (type)
        {
        case ATTACHMENT_REGION:
        {
            if(self->atlas)
            {
                TextureRegion* reg = nullptr;
                try
                {
                    reg = &self->atlas->getRegion(name);
                }
                catch (std::runtime_error e)
                {
                    _AttachmentLoader_setError(loader, "Region not found: ", name);
                    return 0;
                }
                RegionAttachment* attachment = RegionAttachment_create(name);
                attachment->rendererObject = reg;
                const Texture& texture = *self->atlas->getTexture();
                float w = (float)texture.getWidth();
                float h = (float)texture.getHeight();
                float u = reg->x / w;
                float v = reg->y / h;
                float u2, v2;
                if (reg->rotate)
                {
                    u2 = (reg->x + reg->height) / w;
                    v2 = (reg->y + reg->width) / h;
                } else {
                    u2 = (reg->x + reg->width) / w;
                    v2 = (reg->y + reg->height) / h;
                }

                RegionAttachment_setUVs(attachment, u, v, u2, v2, reg->rotate);
                attachment->regionOffsetX = reg->offsetX;
                attachment->regionOffsetY = reg->offsetY;
                attachment->regionWidth = reg->width;
                attachment->regionHeight = reg->height;
                attachment->regionOriginalWidth = reg->originalWidth;
                attachment->regionOriginalHeight = reg->originalHeight;
                return SUPER(attachment);
            }
            return 0;
        }            
        default:
            _AttachmentLoader_setUnknownTypeError(loader, type);
            return 0;
        }
    }    

    AtlasAttachmentLoader* AtlasAttachmentLoader_create(TextureAtlas* atlas)
    {
        AtlasAttachmentLoader* self = NEW(AtlasAttachmentLoader);
        _AttachmentLoader_init(SUPER(self), _AttachmentLoader_deinit, _AtlasAttachmentLoaderr_newAttachment);
        self->atlas = atlas;
        return self;
    }

#pragma mark - spine skeleton loader

    SpineSkeletonLoader::SpineSkeletonLoader()
    {
    }

    bool SpineSkeletonLoader::validate(std::istream& input) const
    {
        std::string str((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
        AtlasAttachmentLoader* loader = AtlasAttachmentLoader_create(nullptr);
        SkeletonJson* json = SkeletonJson_createWithLoader(SUPER(loader));
        SkeletonData *skeletonData = SkeletonJson_readSkeletonData(json, str.c_str());    
        if(skeletonData != nullptr)
        {
            SkeletonData_dispose(skeletonData);
            SkeletonJson_dispose(json);
            return true;
        }
        return false;
    }

    std::unique_ptr<Skeleton> SpineSkeletonLoader::load(std::istream& input) const
    {
        std::unique_ptr<Skeleton> skel(new Skeleton());
        return skel;
    }
      
    void SpineSkeletonLoader::setTextureAtlasManager(AssetManager<TextureAtlas>& mng)
    {
        _textureAtlasManager = &mng;
    }

}
