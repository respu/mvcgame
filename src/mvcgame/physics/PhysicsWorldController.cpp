
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

	b2Vec2 PhysicsWorldController::convertToWorld(const Point& p)
	{
		return b2Vec2(p.x/_scale, p.y/_scale);
	}

	b2Vec2 PhysicsWorldController::convertToWorld(const Size& s)
	{
		return b2Vec2(s.width/_scale, s.height/_scale);
	}

	Point PhysicsWorldController::convertFromWorld(const b2Vec2& v)
	{
		return Point(v.x*_scale, v.y*_scale);
	}

	void PhysicsWorldController::respondOnUpdate(const UpdateEvent& event)
	{
		_world->Step(event.getInterval().fsecs(), _velocityIterations, _positionIterations);
	}

	b2World& PhysicsWorldController::getWorld()
	{
		return *_world;
	}

    const b2World& PhysicsWorldController::getWorld() const
    {
		return *_world;
    }

    PhysicsWorldController::Body& PhysicsWorldController::createBody(b2BodyDef* def)
    {
    	auto bodyPtr = std::unique_ptr<Body>(new Body(*this, def));
    	auto& body = *bodyPtr;
    	addChild(std::move(bodyPtr));
    	return body;
    }
}