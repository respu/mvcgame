
#include <mvcgame/physics/PhysicsShape.hpp>


namespace mvcgame {

	PhysicsShape::PhysicsShape()
	{
	}

	std::ostream& operator<<(std::ostream& os, const PhysicsShape& s)
	{
		os << "PhysicsShape(";
        os << ")";
        return os;
	}
}