
#include <mvcgame/physics/PhysicsBodyController.hpp>
#include <mvcgame/physics/PhysicsWorldController.hpp>
#include <mvcgame/view/View.hpp>
#include <mvcgame/event/Events.hpp>
#include <Box2D/Box2D.h>

namespace mvcgame {

	PhysicsBodyController::PhysicsBodyController(PhysicsWorldController& world, b2BodyDef* def) :
	_body(nullptr), _world(world)
	{
        if(!def)
        {
            def = new b2BodyDef();
            def->type = b2_dynamicBody;
        }
        _body = _world.getWorld().CreateBody(def);
	}

	PhysicsBodyController::~PhysicsBodyController()
	{
	}

    b2Body& PhysicsBodyController::getBody()
    {
    	return *_body;
    }

    const b2Body& PhysicsBodyController::getBody() const
    {
    	return *_body;
    }

    void PhysicsBodyController::setView(std::shared_ptr<View> view)
    {
        ViewController::setView(view);
        updateBody();
    }

    b2Fixture* PhysicsBodyController::addFixture(b2FixtureDef* def)
    {
        if(!def->shape)
        {
            // default shape is the view frame
            auto view = getView();
            assert(view);
            b2Vec2 size = convertToWorld(view->getFrame().size);
            b2PolygonShape* box = new b2PolygonShape();
            box->SetAsBox(size.x/2.0f, size.y/2.0f);
            def->shape = box;
        }
        return _body->CreateFixture(def);
    }

    void PhysicsBodyController::updateBody()
    {
        auto view = getView();
        if(view)
        {
            b2Vec2 p = convertToWorld(view->getFrame().origin-view->getAnchorPoint());
            _body->SetTransform(p, view->getRotation().x);
        }
    }

    void PhysicsBodyController::respondOnUpdate(const UpdateEvent& event)
    {
        auto view = getView();
    	if(view)
    	{       
    		view->getFrame().origin = convertFromWorld(_body->GetPosition())+view->getAnchorPoint();
    		view->setRotation(_body->GetAngle());
    	}
    }

    b2Vec2 PhysicsBodyController::convertToWorld(const Point& p)
    {
        return _world.convertToWorld(p);
    }

    b2Vec2 PhysicsBodyController::convertToWorld(const Size& s)
    {
        return _world.convertToWorld(s);
    }

    Point PhysicsBodyController::convertFromWorld(const b2Vec2& v)
    {
        return _world.convertFromWorld(v);
    }

}