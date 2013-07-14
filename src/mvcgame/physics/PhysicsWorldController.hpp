
#ifndef mvcgame_PhysicsWorldController_hpp
#define mvcgame_PhysicsWorldController_hpp

#include <mvcgame/controller/ViewController.hpp>
#include <map>

class b2World;
class b2Vec2;

namespace mvcgame {

    class Point;

    class PhysicsWorldController : public ViewController
    {
    private:
        unsigned _scale;        
        b2World* _world;
        unsigned _velocityIterations;
        unsigned _positionIterations;

        b2Vec2 convertPoint(const Point& p);
    public:
        PhysicsWorldController(unsigned scale, const Accel& gravity=Accel(0.f, 9.8f));
        ~PhysicsWorldController();

        void controllerAdded();
        void respondOnUpdate(const UpdateEvent& event);
    };
}

#endif