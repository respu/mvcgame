//
//  ITexturePool.h
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_ITexturePool_hpp
#define mvcgame_ITexturePool_hpp

#include <mvcgame/view/ITexture.hpp>

namespace mvcgame {

	class ITexturePool
	{

	public:
		Itexture& getTexture(const std::string& name);
	};
}

#endif