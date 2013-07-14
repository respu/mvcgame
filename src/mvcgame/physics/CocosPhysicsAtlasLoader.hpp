
#ifndef mvcgame_CocosPhysicsAtlasLoader_hpp
#define mvcgame_CocosPhysicsAtlasLoader_hpp

#include <mvcgame/asset/IAssetLoader.hpp>
#include <memory>

namespace mvcgame {

    class PhysicsAtlas;
    class CocosPhysicsAtlasLoaderBridge;

	class CocosPhysicsAtlasLoader : public IAssetLoader<PhysicsAtlas>
	{
	private:
		CocosPhysicsAtlasLoaderBridge* _bridge;
    public:
        CocosPhysicsAtlasLoader();
        ~CocosPhysicsAtlasLoader();        
        bool validate(std::istream& input) const;
        std::shared_ptr<PhysicsAtlas> load(std::istream& input) const;
	};

}

#endif