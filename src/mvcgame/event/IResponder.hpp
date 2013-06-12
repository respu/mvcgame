
#ifndef mvcgame_IResponder_hpp
#define mvcgame_IResponder_hpp

#include <mvcgame/event/Events.hpp>

namespace mvcgame {

    /**
     * Base interface that represents an object that responds to events.
     */
    class IResponder
    {
    public:

        virtual void respondOnUpdate(UpdateEvent& event)
        {
        }

        /**
         * Called before a touch event to decide if a responder
         * has the event inside. Return true if the touch point is inside
         * the responder.
         */
        virtual bool respondToTouchPoint(const Point& p, const TouchEvent& event)
        {
            return false;
        }

        virtual void respondOnTouchStart(TouchEvent& event)
        {
        }

        virtual void respondOnTouchUpdate(UpdateTouchEvent& event)
        {
        }        

        virtual void respondOnTouchEnd(UpdateTouchEvent& event)
        {
        }
        
    };

}


#endif