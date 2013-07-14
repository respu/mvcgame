
#ifndef mvcgame_PhysicsShape_hpp
#define mvcgame_PhysicsShape_hpp

#include <memory>

namespace mvcgame {

	class PhysicsShape : public std::enable_shared_from_this<PhysicsShape>
	{
	public:
		PhysicsShape();
	};

}

#endif