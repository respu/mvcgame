
#include <mvcgame/physics/PhysicsWorldController.hpp>
#include <mvcgame/event/Events.hpp>
#include <Box2D/Box2D.h>

/**
 * http://veeableful.wordpress.com/2012/02/16/tutorial-getting-started-with-box2d/
 */

namespace mvcgame {

	PhysicsWorldController::PhysicsWorldController(unsigned scale, const Accel& gravity) :
	_scale(scale), _world(new b2World(b2Vec2(gravity.x, gravity.y))),
	_velocityIterations(6), _positionIterations(2)
	{

	}

	PhysicsWorldController::~PhysicsWorldController()
	{
		delete _world;
	}

	void PhysicsWorldController::controllerAdded()
	{
	}

	b2Vec2 PhysicsWorldController::convertPoint(const Point& p)
	{
		return b2Vec2(p.x/_scale, p.y/_scale);
	}

	void PhysicsWorldController::respondOnUpdate(const UpdateEvent& event)
	{
		_world->Step(event.getInterval().fsecs(), _velocityIterations, _positionIterations);
	}

	void PhysicsWorldController::addBody(std::unique_ptr<Body> body)
	{
		addChild(std::move(body));
	}
}