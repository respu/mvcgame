
#ifndef mvcgame_PhysicsBodyController_hpp
#define mvcgame_PhysicsBodyController_hpp

#include <mvcgame/controller/ViewController.hpp>

class b2Body;

namespace mvcgame {

    class Point;
    class PhysicsShape;

    class PhysicsBodyController : public ViewController
    {
    private:    
        b2Body* _body;
        std::shared_ptr<PhysicsShape> _shape;
    public:
        PhysicsBodyController();
        PhysicsBodyController(std::shared_ptr<View> view);
        ~PhysicsBodyController();

        void controllerAdded();

        void setShape(std::shared_ptr<PhysicsShape> shape);

    };
}

#endif