//
//  ITexturePool.h
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef __hydra__ITexturePool__
#define __hydra__ITexturePool__

#include <mvcgame/ITexture.hpp>

namespace mvcgame {

	class ITexturePool
	{

	public:
		Itexture& getTexture(const std::string& name);
	};
}

#endif