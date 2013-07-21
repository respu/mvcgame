
#ifndef mvcgame_PhysicsBodyController_hpp
#define mvcgame_PhysicsBodyController_hpp

#include <mvcgame/controller/ViewController.hpp>

class b2Body;
class b2Vec2;
class b2BodyDef;
class b2FixtureDef;
class b2Fixture;

namespace mvcgame {

    class PhysicsWorldController;

    class PhysicsBodyController : public ViewController
    {
    private:    
        b2Body* _body;
        b2BodyDef* _def;
        PhysicsWorldController& _world;
    public:
        PhysicsBodyController(PhysicsWorldController& world, b2BodyDef& def);
        PhysicsBodyController(PhysicsWorldController& world);
        ~PhysicsBodyController();

        b2Body& getBody();
        const b2Body& getBody() const;

        void setView(std::shared_ptr<View> view);
        void updateBody();
        void respondOnUpdate(const UpdateEvent& event);

        b2Vec2 convertToWorld(const Point& p);
        b2Vec2 convertToWorld(const Size& s);
        Point convertFromWorld(const b2Vec2& v);

        b2Fixture& addFixture(b2FixtureDef& def);
    };
}

#endif