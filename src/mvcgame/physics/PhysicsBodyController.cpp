
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
        delete _def;
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
        b2BodyDef def;
        def.type = b2_dynamicBody;
        _body = _world.getWorld().CreateBody(&def);        
        updateBody();
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
                std::cout << p-anchor << std::endl;
                rootVerts.push_back(convertToWorld(p-anchor));
            }

            shape.Set(&rootVerts.front(), rootVerts.size());
            def.shape = &shape;
        }
        return *_body->CreateFixture(&def);
    }

    void PhysicsBodyController::updateBody()
    {
        auto view = getView();
        if(view)
        {
            b2Vec2 p = convertToWorld(view->getFrame().origin);
            _body->SetTransform(p, -1*view->getRotation().x);
        }
    }

    void PhysicsBodyController::respondOnUpdate(const UpdateEvent& event)
    {     
        auto view = getView();
    	if(view)
    	{
    		view->getFrame().origin = convertFromWorld(_body->GetPosition());
    		view->setRotation(-1*_body->GetAngle());
    	}
        ViewController::respondOnUpdate(event);        
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