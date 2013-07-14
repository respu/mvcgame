
#include <mvcgame/physics/PhysicsAtlas.hpp>


namespace mvcgame {

	PhysicsAtlas::PhysicsAtlas()
	{
	}


	std::ostream& operator<<(std::ostream& os, const PhysicsAtlas& a)
	{
		os << "PhysicsAtlas(";
        os << ")";
        return os;
	}
}
