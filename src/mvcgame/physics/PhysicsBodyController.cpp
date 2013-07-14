
#include <mvcgame/physics/PhysicsBodyController.hpp>
#include <Box2D/Box2D.h>

namespace mvcgame {


	PhysicsBodyController::PhysicsBodyController()
	{
	}	

	PhysicsBodyController::PhysicsBodyController(std::shared_ptr<View> view)
	{
		setView(view);
	}

	PhysicsBodyController::~PhysicsBodyController()
	{
	}

	void PhysicsBodyController::controllerAdded()
	{
	}

	void PhysicsBodyController::setShape(std::shared_ptr<PhysicsShape> shape)
	{
		_shape = shape;
	}

}