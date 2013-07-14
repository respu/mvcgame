
#ifndef mvcgame_PhysicsAtlas_hpp
#define mvcgame_PhysicsAtlas_hpp

#include <memory>
#include <iostream>

namespace mvcgame {

	class PhysicsAtlas : public std::enable_shared_from_this<PhysicsAtlas>
	{
	public:
		PhysicsAtlas();
	};

    std::ostream& operator<<(std::ostream& os, const PhysicsAtlas& a);
}

#endif