
#ifndef mvcgame_PhysicsWorldController_hpp
#define mvcgame_PhysicsWorldController_hpp

#include <mvcgame/controller/ViewController.hpp>
#include <mvcgame/physics/PhysicsBodyController.hpp>

class b2World;
class b2Vec2;
class b2BodyDef;

namespace mvcgame {

    class Point;

    class PhysicsWorldController : public ViewController
    {
    public:
        typedef PhysicsBodyController Body;
    private:
        unsigned _scale;        
        b2World* _world;
        unsigned _velocityIterations;
        unsigned _positionIterations;

    public:
        PhysicsWorldController(unsigned scale, const Accel& gravity=Accel(0.f, -9.8f));
        ~PhysicsWorldController();

        void controllerAdded();
        void respondOnUpdate(const UpdateEvent& event);
        Body& createBody(b2BodyDef& def);
        Body& createBody();

        b2Vec2 convertToWorld(const Point& p);
        b2Vec2 convertToWorld(const Size& s);
        Point convertFromWorld(const b2Vec2& v);        

        b2World& getWorld();
        const b2World& getWorld() const;
    };
}

#endif