
#include <mvcgame/physics/PhysicsBodyController.hpp>
#include <mvcgame/physics/PhysicsWorldController.hpp>
#include <mvcgame/view/View.hpp>
#include <mvcgame/event/Events.hpp>
#include <Box2D/Box2D.h>

namespace mvcgame {

	PhysicsBodyController::PhysicsBodyController(PhysicsWorldController& world) :
	_body(nullptr), _def(nullptr), _world(world)
	{
	}

    PhysicsBodyController::PhysicsBodyController(PhysicsWorldController& world, b2BodyDef& def) :
    _body(nullptr), _def(new b2BodyDef(def)), _world(world)
    {
    }    

	PhysicsBodyController::~PhysicsBodyController()
	{
        if(_def)
        {
            delete _def;
        }
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
        b2BodyDef* def = _def;
        if(!def)
        {
            b2BodyDef ldef;
            ldef.type = b2_dynamicBody;
            def = &ldef;
        }
        def->position = convertToWorld(view->getFrame().origin);
        _body = _world.getWorld().CreateBody(def);
    }

    b2Fixture& PhysicsBodyController::addFixture(b2FixtureDef& def)
    {
        b2PolygonShape shape;
        if(!def.shape)
        {
            // default shape is the view frame
            auto view = getView();
            assert(view);
            Points verts = view->getFrame().getVertices(false);
            Point anchor = view->getAnchorPoint();
            std::vector<b2Vec2> rootVerts;
            for(const Point& p : verts)
            {
                rootVerts.push_back(convertToWorld(p-anchor));
            }

            shape.Set(&rootVerts.front(), rootVerts.size());
            def.shape = &shape;
        }
        return *_body->CreateFixture(&def);
    }

    void PhysicsBodyController::updateBody()
    {

    }

    void PhysicsBodyController::respondOnUpdate(const UpdateEvent& event)
    {     
        auto view = getView();
    	if(view)
    	{
    	   view->getFrame().origin = convertFromWorld(_body->GetWorldCenter());
           // view->setRotation(_body->GetAngle());
    	}
        ViewController::respondOnUpdate(event);        
    }

    b2Vec2 PhysicsBodyController::convertToWorld(const Point& p)
    {
        return _world.convertToWorld(p);
    }

    Point PhysicsBodyController::convertFromWorld(const b2Vec2& v)
    {
        return _world.convertFromWorld(v);
    }

}