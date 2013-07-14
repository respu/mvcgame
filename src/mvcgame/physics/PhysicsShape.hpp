
#ifndef mvcgame_PhysicsShape_hpp
#define mvcgame_PhysicsShape_hpp

#include <memory>
#include <iostream>

namespace mvcgame {

	class PhysicsShape : public std::enable_shared_from_this<PhysicsShape>
	{
	public:
		PhysicsShape();
	};

    std::ostream& operator<<(std::ostream& os, const PhysicsShape& s);
}

#endif